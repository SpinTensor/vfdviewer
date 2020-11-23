#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_stack_treeview.h"

GtkToolbar *stack_tree_toolbar = NULL;
GtkToolButton *stack_tree_toolbar_expand_button = NULL;
GtkToolButton *stack_tree_toolbar_collapse_button = NULL;

void vgtk_build_stack_tree_toolbar(GtkBuilder *builder) {
   stack_tree_toolbar = GTK_TOOLBAR(
      gtk_builder_get_object(builder, "stack_tree_toolbar"));
   stack_tree_toolbar_expand_button = GTK_TOOL_BUTTON(
      gtk_builder_get_object(builder, "stack_tree_toolbar_expand_button"));
   stack_tree_toolbar_collapse_button = GTK_TOOL_BUTTON(
      gtk_builder_get_object(builder, "stack_tree_toolbar_collapse_button"));

   gtk_builder_connect_signals(builder, NULL);
}

// Callback function if expand button is clicked
void on_stack_tree_toolbar_expand_button_clicked(GtkToolButton *button) {
   (void) button;
   vgtk_stack_tree_expand();
}

// Callback function if collapse button is clicked
void on_stack_tree_toolbar_collapse_button_clicked(GtkToolButton *button) {
   (void) button;
   vgtk_stack_tree_collapse();
}
