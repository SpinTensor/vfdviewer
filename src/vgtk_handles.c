#include <stdlib.h>

#include <gtk/gtk.h>

#include "vfd_types.h"
#include "vgtk_handles.h"
#include "vgtk_stacktimeline_entry.h"

vgtk_handles_t *new_vgtk_handles() {
   vgtk_handles_t *handles = (vgtk_handles_t*) malloc(sizeof(vgtk_handles_t));
   handles->stackTimelineEntry = new_stackTimelineEntry();
   return handles;
}

void free_vgtk_handles(vgtk_handles_t **handles_ptr) {

   vgtk_handles_t *handles = *handles_ptr;
   free_stackTimelineEntry(&(handles->stackTimelineEntry));

   free(handles);
   handles = NULL;
}
