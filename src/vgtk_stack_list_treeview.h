#ifndef VGTK_STACK_LIST_TREEVIEW_H
#define VGTK_STACK_LIST_TREEVIEW_H

#include <gtk/gtk.h>

#include "vfd_types.h"

void vgtk_build_stack_list_treeview(GtkBuilder *builder);

void vgtk_stack_list_add_vfdtrace(vfd_t *vfdtrace);

#endif
