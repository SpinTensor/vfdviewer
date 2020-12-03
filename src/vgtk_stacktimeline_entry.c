#include <stdlib.h>

#include <gtk/gtk.h>

#include "vfd_types.h"
#include "vgtk_stacktimeline_entry.h"

vgtk_stackTimelineEntry_t *new_stackTimelineEntry() {
   vgtk_stackTimelineEntry_t *stackTimelineEntry =
      (vgtk_stackTimelineEntry_t*) malloc(sizeof(vgtk_stackTimelineEntry_t));
   return stackTimelineEntry;
}

void init_stacktimeline_entry(vfd_t *vfdtrace) {
   ;
//   // create a new drawing area and add it to the vfd-trace
//   vfdtrace->vgtk_handles->stackTimelineDrawingArea =
//      GTK_DRAWING_AREA(gtk_drawing_area_new());
//   // set a minimum width to the drawing area
//   //
//
//   // add the new drawing area as a widget to the stacktimeline timeline box
//   gtk_box_pack_start(main_view_main_stacktimeline_timeline_box,
//                      GTK_WIDGET(vfdtrace->vgtk_handles->stackTimelineDrawingArea),
//                      FALSE,
//                      FALSE,
//                      2);
//   gtk_widget_show_all(GTK_WIDGET(main_view_main_stacktimeline_timeline_box));

}

void free_stackTimelineEntry(vgtk_stackTimelineEntry_t **stackTimelineEntry_ptr) {
   vgtk_stackTimelineEntry_t *stackTimelineEntry = *stackTimelineEntry_ptr;


   free(stackTimelineEntry);
   stackTimelineEntry = NULL;
}
