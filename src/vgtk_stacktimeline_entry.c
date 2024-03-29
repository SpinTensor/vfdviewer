#include <stdlib.h>

#include <math.h>
#include <gtk/gtk.h>

#include "vgtk_types.h"
#include "vfd_types.h"
#include "vfd_list.h"

#include "vgtk_stack_treeview.h"
#include "vgtk_stack_tree_searchentry.h"
#include "vgtk_stacktimeline_entry.h"
#include "vgtk_main_stacktimeline.h"
#include "vgtk_stacktimeline_spinner.h"
#include "vgtk_stacktimeline_checkbuttons.h"
#include "vgtk_stacktimeline_cursorpos_labels.h"
#include "vgtk_comm_matrix.h"
#include "vgtk_surfaces.h"
#include "vgtk_colors.h"

double tmin_stacktimeline_draw = 0.0;
double tmax_stacktimeline_draw = 0.0;
int hmax_stacktimeline_draw = 0;

// Callback declarations
static gboolean vgtk_stacktimeline_entry_configure_callback(
   GtkWidget *widget,
   GdkEventConfigure *event,
   gpointer data);
static gboolean vgtk_stacktimeline_draw_callback(
   GtkWidget *widget,
   cairo_t *cr,
   gpointer data);
void vgtk_stacktimeline_button_press_callback(
   GtkWidget *widget,
   GdkEventButton *event,
   gpointer data);
void vgtk_stacktimeline_button_release_callback(
   GtkWidget *widget,
   GdkEventButton *event,
   gpointer data);
gboolean vgtk_stacktimeline_motion_notify_callback(
   GtkWidget *widget,
   GdkEventMotion *event,
   gpointer data);
gboolean vgtk_stacktimeline_query_tooltip_callback(
   GtkWidget *widget,
   gint x, gint y,
   gboolean keyboard,
   GtkTooltip *tooltip,
   gpointer data);

vgtk_stackTimelineEntry_t *new_stackTimelineEntry() {
   vgtk_stackTimelineEntry_t *stackTimelineEntry =
      (vgtk_stackTimelineEntry_t*) malloc(sizeof(vgtk_stackTimelineEntry_t));
   stackTimelineEntry->surface = NULL;
   stackTimelineEntry->drawing_area = NULL;

   return stackTimelineEntry;
}

void init_stacktimeline_entry(vfd_t *vfdtrace) {
   vgtk_stackTimelineEntry_t *entry = vfdtrace->vgtk_handles->stackTimelineEntry;
   // create a new drawing area and add it to the vfd-trace
   entry->drawing_area =
      GTK_DRAWING_AREA(gtk_drawing_area_new());
   // set a minimum width to the drawing area
   vgtk_set_drawing_area_size(entry->drawing_area);

   // Signals used to handle the backing surface
   g_signal_connect(entry->drawing_area,
                    "draw",
                    G_CALLBACK(vgtk_stacktimeline_draw_callback),
                    (gpointer) vfdtrace);
   g_signal_connect(entry->drawing_area,
                    "configure-event",
                    G_CALLBACK(vgtk_stacktimeline_entry_configure_callback),
                    (gpointer) vfdtrace);

   // Define non-standard widget events.
   g_signal_connect(entry->drawing_area,
                    "button-press-event",
                    G_CALLBACK(vgtk_stacktimeline_button_press_callback),
                    (gpointer) vfdtrace);
   gtk_widget_set_events(GTK_WIDGET(entry->drawing_area),
                         gtk_widget_get_events(GTK_WIDGET(entry->drawing_area))
                            | GDK_BUTTON_PRESS_MASK);
   g_signal_connect(entry->drawing_area,
                    "button-release-event",
                    G_CALLBACK(vgtk_stacktimeline_button_release_callback),
                    (gpointer) vfdtrace);
   gtk_widget_set_events(GTK_WIDGET(entry->drawing_area),
                         gtk_widget_get_events(GTK_WIDGET(entry->drawing_area))
                            | GDK_BUTTON_RELEASE_MASK);
   g_signal_connect(entry->drawing_area,
                    "motion-notify-event",
                    G_CALLBACK(vgtk_stacktimeline_motion_notify_callback),
                    (gpointer) vfdtrace);
   gtk_widget_set_events(GTK_WIDGET(entry->drawing_area),
                         gtk_widget_get_events(GTK_WIDGET(entry->drawing_area))
                            | GDK_POINTER_MOTION_MASK);

   // define the tooltip
   gtk_widget_set_has_tooltip(GTK_WIDGET(entry->drawing_area), TRUE);
   g_signal_connect(entry->drawing_area,
                    "query-tooltip",
                    G_CALLBACK(vgtk_stacktimeline_query_tooltip_callback),
                    (gpointer) vfdtrace);

   // set default button press values
   entry->buttonactive = false;
   entry->buttonpressx = 0.0;
   entry->buttonpressy = 0.0;
   entry->movex = 0.0;
   entry->movey = 0.0;


   // add the new drawing area as a widget to the stacktimeline timeline box
   gtk_box_pack_start(main_stacktimeline_timeline_box,
                      GTK_WIDGET(entry->drawing_area),
                      FALSE,
                      FALSE,
                      2);
   gtk_widget_show_all(GTK_WIDGET(main_stacktimeline_timeline_box));
}

void free_stackTimelineEntry(vgtk_stackTimelineEntry_t **stackTimelineEntry_ptr) {
   vgtk_stackTimelineEntry_t *stackTimelineEntry = *stackTimelineEntry_ptr;

   // destroy surface
   free_surface(&(stackTimelineEntry->surface));

   // destroy drawing area
   gtk_widget_destroy(GTK_WIDGET(stackTimelineEntry->drawing_area));
   stackTimelineEntry->drawing_area = NULL;

   free(stackTimelineEntry);
   stackTimelineEntry = NULL;
}

static gboolean vgtk_stacktimeline_entry_configure_callback(
   GtkWidget *widget,
   GdkEventConfigure *event,
   gpointer data) {

   (void) event;

   // first cast the data pointer to the appropiate data format pointer
   vfd_t *vfdtrace = (vfd_t*) data;

   vgtk_stackTimelineEntry_t *entry = vfdtrace->vgtk_handles->stackTimelineEntry;

   if (entry->surface != NULL) {
      cairo_surface_destroy (entry->surface);
   }

   entry->surface = gdk_window_create_similar_surface(
      gtk_widget_get_window (widget),
      CAIRO_CONTENT_COLOR,
      gtk_widget_get_allocated_width (widget),
      gtk_widget_get_allocated_height (widget));

   vgtk_draw_stacktimeline(entry->drawing_area,
                           entry->surface,
                           vfdtrace);

   return TRUE;
}

static gboolean vgtk_stacktimeline_draw_callback(
   GtkWidget *widget,
   cairo_t   *cr,
   gpointer   data) {

   (void) widget;

   // first cast the data pointer to the appropiate data format pointer
   vfd_t *vfdtrace = (vfd_t*) data;

   vgtk_stackTimelineEntry_t *entry = vfdtrace->vgtk_handles->stackTimelineEntry;

   cairo_set_source_surface(cr, entry->surface, 0, 0);
   cairo_paint(cr);

   return FALSE;
}

void vgtk_draw_stacktimeline(
   GtkDrawingArea *drawing_area,
   cairo_surface_t *surface,
   vfd_t *vfdtrace) {

   // get surface dimensions
   int sfwidth = gtk_widget_get_allocated_width(GTK_WIDGET(drawing_area));
   int sfheight = gtk_widget_get_allocated_height(GTK_WIDGET(drawing_area));

   // get maximum level and max runtime to derive image scaling parameters
   int maxlvl = vfds_max_maxlevel();
   double maxrt = vfds_max_runtime();

   // +2 on the max level because it starts at 0 and needs some space on top
   double scalex = ((double) sfwidth*stacktimeline_xzoom_spinner_get_value()) / maxrt;
   double scaley = ((double) sfheight) / ((double) maxlvl+2);

   // clear surface before painting
   clear_surface(surface);

   // loop over all fcalls (TODO: more efficient) and draw
   cairo_t *cr;
   cr = cairo_create (surface);

   // draw the mpi traffic indicators in the background
   if (stacktimeline_show_mpi_send_checkbutton_checked()) {
      cairo_set_source_rgba(cr,
                            130.0/255.0,
                            160.0/255.0,
                            255.0/255.0,
                            0.5);

      unsigned int nmsg = vfdtrace->header->msgregsendcount;
      for (unsigned int imsg=0; imsg<nmsg; imsg++) {
         if (vfdtrace->msgregs_send[imsg].entry_time > tmax_stacktimeline_draw) {
            // only draw until the first message region later
            // than the max_drawtime is encountered.
            // They are sorted, thus no one should be forgotten.
            break;
         } else if (vfdtrace->msgregs_send[imsg].exit_time > tmin_stacktimeline_draw) {
            // only draw if the end time falls into the selected window
            double width;
            width = vfdtrace->msgregs_send[imsg].exit_time;
            width -= vfdtrace->msgregs_send[imsg].entry_time;
            width *= scalex;

            // only draw the message sample if it is larger than half a pixel
            if (width > 1.0) {
               double x;
               x = vfdtrace->msgregs_send[imsg].entry_time;
               x -= tmin_stacktimeline_draw;
               x *= scalex;

               double y = 0.0;

               double height = sfheight;

               cairo_rectangle(cr,
                               x, y,
                               width, height);

               cairo_fill(cr);
            }
         }
      }
   }
   if (stacktimeline_show_mpi_recv_checkbutton_checked()) {
      cairo_set_source_rgba(cr,
                            255.0/255.0,
                            130.0/255.0,
                            160.0/255.0,
                            0.5);
      unsigned int nmsg = vfdtrace->header->msgregrecvcount;
      for (unsigned int imsg=0; imsg<nmsg; imsg++) {
         if (vfdtrace->msgregs_recv[imsg].entry_time > tmax_stacktimeline_draw) {
            // only draw until the first message region later
            // than the max_drawtime is encountered.
            // They are sorted, thus no one should be forgotten.
            break;
         } else if (vfdtrace->msgregs_recv[imsg].exit_time > tmin_stacktimeline_draw) {
            // only draw if the end time falls into the selected window
            double width;
            width = vfdtrace->msgregs_recv[imsg].exit_time;
            width -= vfdtrace->msgregs_recv[imsg].entry_time;
            width *= scalex;

            // only draw the message sample if it is larger than half a pixel
            if (width > 1.0) {
               double x;
               x = vfdtrace->msgregs_recv[imsg].entry_time;
               x -= tmin_stacktimeline_draw;
               x *= scalex;

               double y = 0.0;

               double height = sfheight;

               cairo_rectangle(cr,
                               x, y,
                               width, height);

               cairo_fill(cr);
            }
         }
      }
   }

   // draw function samples
   for (unsigned int ifcall=0; ifcall<vfdtrace->header->fcallscount; ifcall++) {
      unsigned int stackID = vfdtrace->fcalls[ifcall].stackID;

      if (vfdtrace->fcalls[ifcall].entry_time > tmax_stacktimeline_draw) {
         // only draw until the first stacktimeline entry larger
         // than the max_drawtime is encountered.
         // They are sorted, thus no one should be forgotten.
         break;
      } else if (vfdtrace->fcalls[ifcall].exit_time > tmin_stacktimeline_draw) {
         // only draw if the exit time falls into the selected window
         double width;
         width = vfdtrace->fcalls[ifcall].exit_time;
         width -= vfdtrace->fcalls[ifcall].entry_time;
         width *= scalex;

         // only draw the function if it is larger than half a pixel
         if (width >= 0.5) {
            double x;
            x = vfdtrace->fcalls[ifcall].entry_time;
            x -= tmin_stacktimeline_draw;
            x *= scalex;

            double y;
            y = maxlvl - vfdtrace->stacks[stackID].level+1;
            y *= scaley;

            double height;
            height = scaley;

            vgtk_color_t col;
            if (vfdtrace->stacks[stackID].visible_in_treeview) {
               col = vfdtrace->stacks[stackID].drawcolor;
            } else {
               col = vgtk_color2grayscale(vfdtrace->stacks[stackID].drawcolor);
            }
            cairo_set_source_rgba(cr,
                                  col.red,
                                  col.green,
                                  col.blue,
                                  col.alpha);

            cairo_rectangle(cr,
                            x, y,
                            width, height);

            cairo_fill(cr);
         }
      }
   }

   // write the vfd-filename in the top left corner
   cairo_set_source_rgba(cr, 0.1, 0.1, 0.1, 1.0);

   const double font_size = 12;
   cairo_set_font_size(cr, font_size);
   cairo_move_to(cr, 0, font_size);
   cairo_show_text(cr, vfdtrace->filename);

   // draw mouse zoom marker
   vgtk_stackTimelineEntry_t *entry = vfdtrace->vgtk_handles->stackTimelineEntry;
   if (entry->buttonactive) {
      cairo_set_source_rgba(cr,
                            0.0/255.0,
                            153.0/255.0,
                            0.0/255.0,
                            0.4);

      double x = entry->buttonpressx;
      double width = entry->movex - entry->buttonpressx;
      double y = 0.0;
      double height = sfheight;

      if (width > 2) {
         cairo_rectangle(cr,
                         x, y,
                         width, height);
         cairo_fill(cr);
      }
   }

   // destroy cairo
   cairo_destroy(cr);

   // actually draw the queued actions
   gtk_widget_queue_draw(GTK_WIDGET(drawing_area));

}

void vgtk_set_drawing_area_size(GtkDrawingArea *drawing_area) {

   int maxlvl = vfds_max_maxlevel();

   double yzoom = stacktimeline_yzoom_spinner_get_value();

   gtk_widget_set_size_request(GTK_WIDGET(drawing_area),
                               128,
                               yzoom*maxlvl);
}

// loop over all vfdtraces and redraw the stacktimeline
void vgtk_redraw_all_stacktimelines() {
   vfd_t *vfdtrace = first_vfd();
   while (vfdtrace != NULL) {
      vgtk_set_drawing_area_size(
         vfdtrace->vgtk_handles->stackTimelineEntry->drawing_area);
      vgtk_draw_stacktimeline(
         vfdtrace->vgtk_handles->stackTimelineEntry->drawing_area,
         vfdtrace->vgtk_handles->stackTimelineEntry->surface,
         vfdtrace);
      vfdtrace = vfdtrace->next;
   }
}

double get_tmin_stacktimeline_draw() {
   return tmin_stacktimeline_draw;
}

double get_tmax_stacktimeline_draw() {
   return tmax_stacktimeline_draw;
}

void set_tmin_stacktimeline_draw(double new_time) {
   tmin_stacktimeline_draw = new_time >= 0.0 ? new_time : 0.0;
   set_tmin_stacktimeline_draw_label(tmin_stacktimeline_draw);
   set_tcen_stacktimeline_draw_label(
      0.5*(tmin_stacktimeline_draw+tmax_stacktimeline_draw));

   // now the communication matrix needs to be redrawn.
   // However, it is more efficient to invalidate the data
   // and draw once it is displayed
   comm_matrix_invalidate();
}

void set_tmax_stacktimeline_draw(double new_time) {
   double tmptime = vfds_max_runtime();
   tmax_stacktimeline_draw = new_time <= tmptime ? new_time : tmptime;
   set_tmax_stacktimeline_draw_label(tmax_stacktimeline_draw);
   set_tcen_stacktimeline_draw_label(
      0.5*(tmin_stacktimeline_draw+tmax_stacktimeline_draw));

   // now the communication matrix needs to be redrawn.
   // However, it is more efficient to invalidate the data
   // and draw once it is displayed
   comm_matrix_invalidate();
}

int get_hmax_stacktimeline_draw() {
   return hmax_stacktimeline_draw;
}

void set_hmax_stacktimeline_draw(int new_height) {
   int tmpheight = vfds_max_maxlevel() + 2;
   hmax_stacktimeline_draw = new_height >= tmpheight ? new_height : tmpheight;
}

void vgtk_stacktimeline_button_press_callback(
   GtkWidget *widget,
   GdkEventButton *event,
   gpointer data) {

   (void) widget;

   vfd_t *vfdtrace = (vfd_t*) data;
   vgtk_stackTimelineEntry_t *entry = vfdtrace->vgtk_handles->stackTimelineEntry;
   entry->buttonactive = true;
   entry->buttonpressx = event->x;
   entry->movex = entry->buttonpressx;
   entry->buttonpressy = event->y;
   entry->movey = entry->buttonpressy;
#ifdef _DEBUG
   printf("Button Press event at vfd=%d, x=%f, y=%f\n",
          vfd_position(vfdtrace), entry->buttonpressx, entry->buttonpressy);
#endif
}

void vgtk_stacktimeline_button_release_callback(
   GtkWidget *widget,
   GdkEventButton *event,
   gpointer data) {

   // a static string to hold a temporary version of a function name
   // with "^" in the beginning and "$" in the end
   // to enable precise function name matching
   // with regular expressions
   static char *precise_name_matcher = NULL;

   vfd_t *vfdtrace = (vfd_t*) data;
   vgtk_stackTimelineEntry_t *entry = vfdtrace->vgtk_handles->stackTimelineEntry;
   entry->buttonactive = false;
#ifdef _DEBUG
   printf("Button release event at vfd=%d, x=%f, y=%f\n",
          vfd_position(vfdtrace), entry->buttonpressx, entry->buttonpressy);
#endif

   GtkDrawingArea *drawing_area = GTK_DRAWING_AREA(widget);

   // get surface dimensions
   int sfwidth = gtk_widget_get_allocated_width(GTK_WIDGET(drawing_area));
   int sfheight = gtk_widget_get_allocated_height(GTK_WIDGET(drawing_area));

   // only select a function for stack filtering if the mouse was barely moved
   // between button press and release
   if (fabs(entry->buttonpressx - event->x) > 2.0) {
      double ntmin;
      double ntmax;
      if (entry->buttonpressx > event->x) {
         ntmin = event->x;
         ntmax = entry->buttonpressx;
      } else {
         ntmin = entry->buttonpressx;
         ntmax = event->x;
      }

      // compute the new min and max drawtimes
      ntmin = ntmin < 0.0 ? 0.0 : ntmin;
      ntmin /= sfwidth;
      ntmin *= (tmax_stacktimeline_draw - tmin_stacktimeline_draw);
      ntmin += tmin_stacktimeline_draw;

      ntmax = ntmax > sfwidth ? sfwidth : ntmax;
      ntmax /= sfwidth;
      ntmax *= (tmax_stacktimeline_draw - tmin_stacktimeline_draw);
      ntmax += tmin_stacktimeline_draw; 

      double tmax_abs = vfds_max_runtime();
      double ntcen = 0.5*(ntmin + ntmax);
      double newscale = 2.0*(ntcen - ntmin)/tmax_abs; 

      // set the new zoom values via the spinner signal
      set_tmin_stacktimeline_draw(ntmin);
      set_tmax_stacktimeline_draw(ntmax);
      stacktimeline_xzoom_spinner_set_value(1.0/newscale);
   } else {
      // get maximum level and max runtime to derive image scaling parameters
      int maxlvl = vfds_max_maxlevel();
   
      int level = (int) ((maxlvl+2) * (1.0 - event->y / sfheight));
      double time;
      time = event->x / sfwidth;
      time *= (tmax_stacktimeline_draw - tmin_stacktimeline_draw);
      time += tmin_stacktimeline_draw;
   
      set_stacktimeline_cursorpos_label(time, level);
   
   #ifdef _DEBUG
      fprintf(stderr, "\n");
      fprintf(stderr, "Stacktimeline click:\n");
      fprintf(stderr, "   x=%f, y=%f\n", event->x, event->y);
      fprintf(stderr, "   time=%f, level=%d\n", time, level);
   #endif
   
      // search for the function call in the stacktimeline
      // that fits the time and level of the click
      bool found_funtion = false;
      vfd_fcall_t fcall;
      unsigned int stackID = -1;
      for (unsigned int ifcall=0; ifcall<vfdtrace->header->fcallscount; ifcall++) {
         fcall = vfdtrace->fcalls[ifcall];
         stackID = vfdtrace->fcalls[ifcall].stackID;
   
         found_funtion = fcall.entry_time < time &&
                         fcall.exit_time > time &&
                         vfdtrace->stacks[stackID].level == level;
         if (found_funtion) {break;}
      }
   
      // select the function in stack tree
      // first get the index list
      int *indices = NULL;
      int nidx = 0;
      indexlist_from_vfd_trace_and_stack(vfdtrace, (vfdtrace->stacks)+stackID,
                                         &nidx, &indices);
      // select a the function in the stack tree view
      stack_tree_select_entry_from_indices(nidx, indices);
      free(indices);
   
      if (found_funtion) {
   #ifdef _DEBUG
         fprintf(stderr, "   stackID=%u\n", stackID);
         fprintf(stderr, "   name=%s\n", vfdtrace->stacks[stackID].name);
   #endif
   
         // prepare the name of the matched function
         // for exact regular expression matching
         int namelen = strlen(vfdtrace->stacks[stackID].name);
         int lnamelen = namelen + 2; // "^","$"
         // reallocate stringbuffer if required
         if (precise_name_matcher == NULL) {
            precise_name_matcher = (char*) malloc((lnamelen+1)*sizeof(char));
         } else {
            if ((size_t) lnamelen > strlen(precise_name_matcher)) {
               free(precise_name_matcher);
               precise_name_matcher = (char*) malloc((lnamelen+1)*sizeof(char));
            }
         }
         // construct string
         // first char needs to be "^" to mark beginning of text input for regex
         precise_name_matcher[0] = '^';
         // next the function name
         strcpy(precise_name_matcher+1, vfdtrace->stacks[stackID].name);
         // append a "$" char to indicate the end of the string input
         precise_name_matcher[namelen+1] = '$';
         // don't forget the null terminator
         precise_name_matcher[namelen+2] = '\0';
   
         // enter the regular expresion into the searchbar
         vgtk_stack_tree_searchentry_set_text(precise_name_matcher);
   #ifdef _DEBUG
      } else {
         fprintf(stderr, "   No matching stack\n");
   #endif
      }
   }
}

gboolean vgtk_stacktimeline_motion_notify_callback(
   GtkWidget *widget,
   GdkEventMotion *event,
   gpointer data) {

   (void) widget;

   if (event->state & GDK_BUTTON1_MASK) {
      vfd_t *vfdtrace = (vfd_t*) data;
      vgtk_stackTimelineEntry_t *entry = vfdtrace->vgtk_handles->stackTimelineEntry;

      // get the newest cursor pos values
      entry->movex = event->x;
      entry->movey = event->y;

      // redraw only that one timeline
      vgtk_set_drawing_area_size(
         vfdtrace->vgtk_handles->stackTimelineEntry->drawing_area);
      vgtk_draw_stacktimeline(
         vfdtrace->vgtk_handles->stackTimelineEntry->drawing_area,
         vfdtrace->vgtk_handles->stackTimelineEntry->surface,
         vfdtrace);

#ifdef _DEBUG
      printf("Move-notify event at vfd=%d, x=%f, y=%f\n",
             vfd_position(vfdtrace), event->x, event->y);
#endif
   }
   return TRUE;
}

gboolean vgtk_stacktimeline_query_tooltip_callback(
   GtkWidget *widget,
   gint x, gint y,
   gboolean keyboard,
   GtkTooltip *tooltip,
   gpointer data) {

   (void) keyboard;

   GtkDrawingArea *drawing_area = GTK_DRAWING_AREA(widget);
   vfd_t *vfdtrace = (vfd_t*) data;

   // get surface dimensions
   int sfwidth = gtk_widget_get_allocated_width(GTK_WIDGET(drawing_area));
   int sfheight = gtk_widget_get_allocated_height(GTK_WIDGET(drawing_area));

   // get maximum level and max runtime to derive image scaling parameters
   int maxlvl = vfds_max_maxlevel();

   int level = (int) ((maxlvl+2) * (1.0 - ((double) y) / ((double) sfheight)));
   double time;
   time = ((double) x) / ((double) sfwidth);
   time *= (tmax_stacktimeline_draw - tmin_stacktimeline_draw);
   time += tmin_stacktimeline_draw;

   // search for the function call in the stacktimeline
   // that fits the time and level of the click
   bool found_funtion = false;
   vfd_fcall_t fcall;
   unsigned int stackID = -1;
   for (unsigned int ifcall=0; ifcall<vfdtrace->header->fcallscount; ifcall++) {
      fcall = vfdtrace->fcalls[ifcall];
      stackID = vfdtrace->fcalls[ifcall].stackID;

      found_funtion = fcall.entry_time < time &&
                      fcall.exit_time > time &&
                      vfdtrace->stacks[stackID].level == level;
      if (found_funtion) {break;}
   }

   if (found_funtion) {
      // go through all functions down the stack
      // and record their length
      int sumnamelen = 0;
      int tmpstackID = stackID;
      while (tmpstackID != 0) {
         // add function name length
         sumnamelen += strlen(vfdtrace->stacks[tmpstackID].name);
         // add one char for newline characters
         sumnamelen++;
         tmpstackID = vfdtrace->stacks[tmpstackID].callerID;
      }
      // add lowest element by hand (with stackID == 0)
      sumnamelen += strlen(vfdtrace->stacks[tmpstackID].name);
      // add one char for newline characters
      sumnamelen++;

#define LABEL_CONTENT_LEN 16
      char *tooltipstr = (char*) malloc((sumnamelen+LABEL_CONTENT_LEN)*sizeof(char));
      snprintf(tooltipstr,
               (size_t) (LABEL_CONTENT_LEN-1),
               "%4.3les:", time);
      // go through all the functions down the stack
      // and add the name to the tooltip string
      tmpstackID = stackID;
      while (tmpstackID != 0) {
         int tooltipstrlen = strlen(tooltipstr);
         tooltipstr[tooltipstrlen] = '\n';
         tooltipstrlen++;
         strcpy(tooltipstr+tooltipstrlen, vfdtrace->stacks[tmpstackID].name);
         tmpstackID = vfdtrace->stacks[tmpstackID].callerID;
      }
      // add lowest stack element by hand
      int tooltipstrlen = strlen(tooltipstr);
      tooltipstr[tooltipstrlen] = '\n';
      tooltipstrlen++;
      strcpy(tooltipstr+tooltipstrlen, vfdtrace->stacks[tmpstackID].name);

      gtk_tooltip_set_text(tooltip,
                           tooltipstr);
      free(tooltipstr);
      tooltipstr = NULL;
#undef LABEL_CONTENT_LEN
      return TRUE;
   } else {
      return FALSE;
   }
}
