#ifndef VGTK_STACKTIMELINE_ENTRY_H
#define VGTK_STACKTIMELINE_ENTRY_H

#include "vfd_types.h"
#include "vgtk_types.h"

vgtk_stackTimelineEntry_t *new_stackTimelineEntry();

void init_stacktimeline_entry(vfd_t *vfdtrace);

void free_stackTimelineEntry(vgtk_stackTimelineEntry_t **stackTimelineEntry_ptr);

#endif
