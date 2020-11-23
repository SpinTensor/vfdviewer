#include <stdlib.h>
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

void vgtk_stack_tree_add_level(GtkTreeIter *parentIter, vfd_stack_entry_t *stacklevel) {
   GtkTreeIter iter;
   // Add this function to the stacktree
   gtk_tree_store_append(stack_tree_treestore, &iter, parentIter);
   gtk_tree_store_set(stack_tree_treestore, &iter,
                      0, stacklevel->name, -1);
   // recuresively go through all callees fo this function
   for (int icallee=0; icallee<stacklevel->ncallees; icallee++) {
      vgtk_stack_tree_add_level(&iter, stacklevel->callees[icallee]);
   }
}

void vgtk_stack_tree_add_vfdtrace(vfd_t *vfdtrace) {
   GtkTreeIter iter;

   // add vfd name as top level entry
   gtk_tree_store_append(stack_tree_treestore, &iter, NULL);
   gtk_tree_store_set(stack_tree_treestore, &iter,
                      0, vfdtrace->filename, -1);

   // add all stack entries recursively
   // skip init as it has no additional information
   for (int icallee=1; icallee<vfdtrace->stacks->ncallees; icallee++) {
      vgtk_stack_tree_add_level(&iter, vfdtrace->stacks->callees[icallee]);
   }
}
