#ifndef VGTK_STACK_TREEVIEW_H
#define VGTK_STACK_TREEVIEW_H

#include <gtk/gtk.h>

#include "vfd_types.h"

void vgtk_build_stack_treeview(GtkBuilder *builder);

void vgtk_stack_tree_expand();

void vgtk_stack_tree_collapse();

void vgtk_stack_tree_add_vfdtrace(vfd_t *vfdtrace);

void vgtk_stack_tree_remove_selected_vfdtrace();

vfd_t *get_stack_tree_currently_selected_vfdtrace();

void vgtk_stack_tree_refilter();

#endif
