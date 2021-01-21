#include <stdlib.h>

#include <gtk/gtk.h>

#include "vfd_types.h"
#include "vgtk_handles.h"
#include "vgtk_stacktimeline_entry.h"
#include "vgtk_hwc_plot_entry.h"
#include "vgtk_hwc_plot_entry.h"

vgtk_handles_t *new_vgtk_handles() {
   vgtk_handles_t *handles = (vgtk_handles_t*) malloc(sizeof(vgtk_handles_t));
   handles->stackTimelineEntry = new_stackTimelineEntry();
   handles->hwcPlotEntry = new_hwcPlotEntry();
   return handles;
}

void free_vgtk_handles(vgtk_handles_t **handles_ptr) {

   vgtk_handles_t *handles = *handles_ptr;
   free_stackTimelineEntry(&(handles->stackTimelineEntry));
   free_hwcPlotEntry(&(handles->hwcPlotEntry));

   free(handles);
   handles = NULL;
}
