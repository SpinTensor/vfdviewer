#ifndef VGTK_HANDLES_H
#define VGTK_HANDLES_H

#include <gtk/gtk.h>

#include "vgtk_types.h"
#include "vgtk_stacktimeline_entry.h"

vgtk_handles_t *new_vgtk_handles();

void free_vgtk_handles(vgtk_handles_t **handles_ptr);

#endif
