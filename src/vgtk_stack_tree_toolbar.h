#ifndef VGTK_STACK_TREEVIEW_H
#define VGTK_STACK_TREEVIEW_H

#include <gtk/gtk.h>

void vgtk_build_stack_tree_toolbar(GtkBuilder *builder);

// Callback function if expand button is clicked
void on_stack_tree_toolbar_expand_button_clicked(GtkToolButton *button);

// Callback function if collapse button is clicked
void on_stack_tree_toolbar_collapse_button_clicked(GtkToolButton *button);

#endif
