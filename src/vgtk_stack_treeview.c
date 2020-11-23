#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_stack_tree_toolbar.h"
#include "vfd_types.h"
#include "vfd_list.h"

GtkTreeStore *stack_tree_treestore = NULL;
GtkTreeView *stack_tree_treeview = NULL;

GtkTreeViewColumn *stack_tree_treeview_functionnames_column = NULL;
GtkCellRenderer *stack_tree_treeview_functionnames_text = NULL;

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
   stack_tree_treeselection = GTK_TREE_SELECTION(
      gtk_builder_get_object(builder, "stack_tree_treeselection"));

   gtk_tree_view_column_add_attribute(stack_tree_treeview_functionnames_column,
                                      stack_tree_treeview_functionnames_text,
                                      "text", 0);

   stack_tree_treeselection = gtk_tree_view_get_selection(stack_tree_treeview);

   gtk_builder_connect_signals(builder, NULL);

   vgtk_build_stack_tree_toolbar(builder);
}

void vgtk_stack_tree_expand() {
   gtk_tree_view_expand_all(stack_tree_treeview);
}

void vgtk_stack_tree_collapse() {
   gtk_tree_view_collapse_all(stack_tree_treeview);
}

void vgtk_stack_tree_add_vfdtrace(vfd_t *vfdtrace) {
   GtkTreeIter iter;       // iterators
   GtkTreeIter iterChild1; // iterators
   GtkTreeIter iterChild2; // iterators
   
   gtk_tree_store_append(stack_tree_treestore, &iter, NULL);
   gtk_tree_store_set(stack_tree_treestore, &iter, 0, "row 1", -1);
   
   gtk_tree_store_append(stack_tree_treestore, &iterChild1, &iter);
   gtk_tree_store_set(stack_tree_treestore, &iterChild1, 0, "row 1 child", -1);
   
   gtk_tree_store_append(stack_tree_treestore, &iter, NULL);
   gtk_tree_store_set(stack_tree_treestore, &iter, 0, "row 2", -1);
   
   gtk_tree_store_append(stack_tree_treestore, &iterChild1, &iter);
   gtk_tree_store_set(stack_tree_treestore, &iterChild1, 0, "row 2 child", -1);
   
   gtk_tree_store_append(stack_tree_treestore, &iterChild2, &iterChild1);
   gtk_tree_store_set(stack_tree_treestore, &iterChild2, 0, "row 2 child of child", -1);
}
