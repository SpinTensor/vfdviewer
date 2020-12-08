#include <stdlib.h>

#include <gtk/gtk.h>

#include "vgtk_types.h"
#include "vfd_types.h"
#include "vfd_list.h"

#include "vgtk_stacktimeline_entry.h"
#include "vgtk_main_view_main_stacktimeline.h"
#include "vgtk_surfaces.h"
#include "vgtk_colors.h"


// Callback declarations
static gboolean vgtk_stacktimeline_entry_configure_callback(
   GtkWidget *widget,
   GdkEventConfigure *event,
   gpointer data);
static gboolean vgtk_stacktimeline_draw_callback(
   GtkWidget *widget,
   cairo_t *cr,
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
   gtk_widget_set_size_request(GTK_WIDGET(entry->drawing_area), 100, 100);

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
// 
//   /* Event signals */
//   g_signal_connect (drawing_area, "motion-notify-event",
//                     G_CALLBACK (motion_notify_event_cb), NULL);
//   g_signal_connect (drawing_area, "button-press-event",
//                     G_CALLBACK (button_press_event_cb), NULL);
//   gtk_widget_set_events (drawing_area, gtk_widget_get_events (drawing_area)
//                          | GDK_BUTTON_PRESS_MASK
//                          | GDK_POINTER_MOTION_MASK);


   // add the new drawing area as a widget to the stacktimeline timeline box
   gtk_box_pack_start(main_view_main_stacktimeline_timeline_box,
                      GTK_WIDGET(entry->drawing_area),
                      FALSE,
                      FALSE,
                      2);
   gtk_widget_show_all(GTK_WIDGET(main_view_main_stacktimeline_timeline_box));
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
                           vfdtrace,
                           0.0, vfdtrace->header->runtime);

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
   vfd_t *vfdtrace,
   double tstart, double tend) {

   // get surface dimensions
   int sfwidth = gtk_widget_get_allocated_width(GTK_WIDGET(drawing_area));
   int sfheight = gtk_widget_get_allocated_height(GTK_WIDGET(drawing_area));

   // get maximum level and max runtime to derive image scaling parameters
   int maxlvl = vfds_max_maxlevel();
   double maxrt = vfds_max_runtime()*1.0e6;

   // +2 on the max level because it starts at 0 and needs some space on top
   double scalex = ((double) sfwidth) / maxrt;
   double scaley = ((double) sfheight) / ((double) maxlvl+2);

   // clear surface before painting
   clear_surface(surface);
   
   // loop over all fcalls (TODO: more efficient) and draw
   cairo_t *cr;
   cr = cairo_create (surface);

   for (unsigned int ifcall=0; ifcall<vfdtrace->header->fcallscount; ifcall++) {
      unsigned int stackID = vfdtrace->fcalls[ifcall].stackID;

      double x;
      x = vfdtrace->fcalls[ifcall].entry_time;
      x *= scalex;

      double y;
      y = maxlvl - vfdtrace->stacks[stackID].level+1;
      y *= scaley;

      double width;
      width = vfdtrace->fcalls[ifcall].exit_time;
      width -= vfdtrace->fcalls[ifcall].entry_time;
      width *= scalex;

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

   cairo_destroy(cr);

   // actually draw the queued actions
   gtk_widget_queue_draw(GTK_WIDGET(drawing_area));

}
