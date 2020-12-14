#include <stdlib.h>

#include <gtk/gtk.h>

#include "vgtk_types.h"
#include "vfd_types.h"
#include "vfd_list.h"

#include "vgtk_stack_tree_searchentry.h"
#include "vgtk_stacktimeline_entry.h"
#include "vgtk_main_stacktimeline.h"
#include "vgtk_stacktimeline_spinner.h"
#include "vgtk_stacktimeline_checkbuttons.h"
#include "vgtk_stacktimeline_cursorpos_labels.h"
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
//void vgtk_stacktimeline_motion_notify_callback(
//   GtkWidget *widget,
//   GdkEventMotion *event,
//   gpointer data);

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

   // connect the signals TODO
  /* Signals used to handle the backing surface */
   g_signal_connect(entry->drawing_area,
                    "draw",
                    G_CALLBACK(vgtk_stacktimeline_draw_callback),
                    (gpointer) vfdtrace);
   g_signal_connect(entry->drawing_area,
                    "configure-event",
                    G_CALLBACK(vgtk_stacktimeline_entry_configure_callback),
                    (gpointer) vfdtrace);

   // Define non-standard widget events.
//   g_signal_connect(entry->drawing_area,
//                    "motion-notify-event",
//                    G_CALLBACK(vgtk_stacktimeline_motion_notify_callback),
//                    (gpointer) vfdtrace);
   g_signal_connect(entry->drawing_area,
                    "button-press-event",
                    G_CALLBACK(vgtk_stacktimeline_button_press_callback),
                    (gpointer) vfdtrace);
   gtk_widget_set_events(GTK_WIDGET(entry->drawing_area),
                         gtk_widget_get_events(GTK_WIDGET(entry->drawing_area))
                            | GDK_BUTTON_PRESS_MASK);
//                            | GDK_POINTER_MOTION_MASK);


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
   bool show_send = stacktimeline_show_mpi_send_checkbutton_checked();
   bool show_recv = stacktimeline_show_mpi_recv_checkbutton_checked();

   if (show_send || show_recv) {
      unsigned int nmsg = vfdtrace->header->message_samplecount;
      for (unsigned int imsg=0; imsg<nmsg; imsg++) {
         if (vfdtrace->messages[imsg].dtstart_sec > tmax_stacktimeline_draw) {
            // only draw until the first message entry larger
            // than the max_drawtime is encountered.
            // They are sorted, thus no one should be forgotten.
            break;
         } else if (vfdtrace->messages[imsg].dtend_sec > tmin_stacktimeline_draw) {
            if (vfdtrace->messages[imsg].dir == send) {
               if (show_send) {
                  // only draw if the end time falls into the selected window
                  double width;
                  width = vfdtrace->messages[imsg].dtend_sec;
                  width -= vfdtrace->messages[imsg].dtstart_sec;
                  width *= scalex;

                  // only draw the message if it is larger than half a pixel
                  if (width > 1.0) {
                     double x;
                     x = vfdtrace->messages[imsg].dtstart_sec;
                     x -= tmin_stacktimeline_draw;
                     x *= scalex;

                     double y = 0.0;

                     double height = sfheight;

                     cairo_set_source_rgba(cr,
                                           130.0/255.0,
                                           160.0/255.0,
                                           255.0/255.0,
                                           0.5);

                     cairo_rectangle(cr,
                                     x, y,
                                     width, height);

                     cairo_fill(cr);
                  }
               }
            } else {
               if (show_recv) {
                  // only draw if the end time falls into the selected window
                  double width;
                  width = vfdtrace->messages[imsg].dtend_sec;
                  width -= vfdtrace->messages[imsg].dtstart_sec;
                  width *= scalex;

                  // only draw the message if it is larger than half a pixel
                  if (width > 1.0) {
                     double x;
                     x = vfdtrace->messages[imsg].dtstart_sec;
                     x -= tmin_stacktimeline_draw;
                     x *= scalex;

                     double y = 0.0;

                     double height = sfheight;

                     cairo_set_source_rgba(cr,
                                           255.0/255.0,
                                           130.0/255.0,
                                           160.0/255.0,
                                           0.5);

                     cairo_rectangle(cr,
                                     x, y,
                                     width, height);

                     cairo_fill(cr);
                  }
               }
            }
         }
      }
   }

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
}

void set_tmax_stacktimeline_draw(double new_time) {
   double tmptime = vfds_max_runtime();
   tmax_stacktimeline_draw = new_time <= tmptime ? new_time : tmptime;
   set_tmax_stacktimeline_draw_label(tmax_stacktimeline_draw);
   set_tcen_stacktimeline_draw_label(
      0.5*(tmin_stacktimeline_draw+tmax_stacktimeline_draw));
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

   // a static string to hold a temporary version of a function name
   // with "^" in the beginning and "$" in the end
   // to enable precise function name matching
   // with regular expressions
   static char *precise_name_matcher = NULL;

   GtkDrawingArea *drawing_area = GTK_DRAWING_AREA(widget);
   vfd_t *vfdtrace = (vfd_t*) data;

   // get surface dimensions
   int sfwidth = gtk_widget_get_allocated_width(GTK_WIDGET(drawing_area));
   int sfheight = gtk_widget_get_allocated_height(GTK_WIDGET(drawing_area));

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

//void vgtk_stacktimeline_motion_notify_callback(
//   GtkWidget *widget,
//   GdkEventMotion *event,
//   gpointer data) {
//   printf("motion notify\n");
//}
