#include <stdio.h>

#include <gtk/gtk.h>

#include "vfd_list.h"

GtkTreeStore *stack_tree_treestore = NULL;
GtkTreeView *stack_tree_treeview = NULL;

GtkTreeViewColumn *stack_tree_treeview_functionnames_column = NULL;
GtkCellRenderer *stack_tree_treeview_functionnames_text = NULL;

GtkTreeViewColumn *stack_tree_treeview_stackID_column = NULL;
GtkCellRenderer *stack_tree_treeview_stackID_text = NULL;

GtkTreeSelection *stack_tree_treeselection = NULL;

void vgtk_build_stack_treeview(GtkBuilder *builder) {
   stack_tree_treestore = GTK_TREE_STORE(
      gtk_builder_get_object(builder, "stack_tree_treestore"));
   stack_tree_treeview = GTK_TREE_VIEW(
      gtk_builder_get_object(builder, "stack_tree_treeview"));
   stack_tree_treeview_functionnames_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_tree_treeview_functionnames_column"));
   stack_tree_treeview_functionnames_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_tree_treeview_functionnames_text"));
   stack_tree_treeview_stackID_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_tree_treeview_stackID_column"));
   stack_tree_treeview_stackID_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_tree_treeview_stackID_text"));
   stack_tree_treeselection = GTK_TREE_SELECTION(
      gtk_builder_get_object(builder, "stack_tree_treeselection"));

   gtk_tree_view_column_add_attribute(stack_tree_treeview_functionnames_column,
                                      stack_tree_treeview_functionnames_text,
                                      "text", 0);
   gtk_tree_view_column_add_attribute(stack_tree_treeview_stackID_column,
                                      stack_tree_treeview_stackID_text,
                                      "text", 0);

   gtk_builder_connect_signals(builder, NULL);
}
