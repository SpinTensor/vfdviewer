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

// Connect main menu bar callback signals
void vgtk_connect_stack_treeview(GtkBuilder *builder) {
   gtk_builder_connect_signals(builder, NULL);
}
