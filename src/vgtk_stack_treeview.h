#ifndef VGTK_STACK_TREEVIEW_H
#define VGTK_STACK_TREEVIEW_H

#include <gtk/gtk.h>

extern GtkTreeStore *stack_tree_treestore;
extern GtkTreeView *stack_tree_treeview;

extern GtkTreeViewColumn *stack_tree_treeview_functionnames_column;
extern GtkCellRenderer *stack_tree_treeview_functionnames_text;

extern GtkTreeViewColumn *stack_tree_treeview_stackID_column;
extern GtkCellRenderer *stack_tree_treeview_stackID_text;

extern GtkTreeSelection *stack_tree_treeselection;

// Connect main menu bar callback signals
void vgtk_connect_stack_treeview(GtkBuilder *builder);

#endif

