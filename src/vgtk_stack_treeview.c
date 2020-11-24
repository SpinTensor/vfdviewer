#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_stack_tree_toolbar.h"
#include "vgtk_stack_tree_searchentry.h"
#include "vfd_types.h"
#include "vfd_list.h"

GtkTreeStore *stack_tree_treestore = NULL;
GtkTreeView *stack_tree_treeview = NULL;

GtkTreeViewColumn *stack_tree_treeview_functionnames_column = NULL;
GtkCellRenderer *stack_tree_treeview_functionnames_text = NULL;

GtkTreeSelection *stack_tree_treeselection = NULL;

GtkTreeModelFilter *stack_tree_treefilter = NULL;

gboolean stack_tree_determine_visibility(GtkTreeModel *model,
                                         GtkTreeIter *parent,
                                         gpointer data);

gint stack_tree_selected_treepath_depth = 0;
gint *stack_tree_selected_treepath = NULL;

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

   stack_tree_treefilter = GTK_TREE_MODEL_FILTER(
      gtk_builder_get_object(builder, "stack_tree_treefilter"));

   gtk_tree_view_column_add_attribute(stack_tree_treeview_functionnames_column,
                                      stack_tree_treeview_functionnames_text,
                                      "text", 0);

   stack_tree_treeselection = gtk_tree_view_get_selection(stack_tree_treeview);

   gtk_tree_model_filter_set_visible_func(
      GTK_TREE_MODEL_FILTER(stack_tree_treefilter),
      (GtkTreeModelFilterVisibleFunc) stack_tree_determine_visibility,
      NULL, NULL);


   gtk_builder_connect_signals(builder, NULL);

   vgtk_build_stack_tree_searchentry(builder);
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

// reapply the tree filter
void vgtk_stack_tree_refilter() {
   gtk_tree_model_filter_refilter(stack_tree_treefilter);
}

// Function to determine the visibility of stack tree entries
gboolean stack_tree_determine_visibility(GtkTreeModel *model,
                                         GtkTreeIter *iter,
                                         gpointer data) {
   (void) data;

   gboolean retval = FALSE;
   // this node should be visible
   // if any of its children is visible
   GtkTreeIter childiter;
   gboolean has_children;
   has_children = gtk_tree_model_iter_children(model, &childiter, iter);
   if (has_children) {
      // loop over all children of this generation
      do {
         retval = stack_tree_determine_visibility(model, &childiter, data);
      } while (gtk_tree_model_iter_next(model, &childiter) && !retval);
   }

   // if it is still not decided
   // check if this node matches the search entry
   if (!retval) {
      //
      // first get the search entry text
      const gchar *search_text = vgtk_stack_tree_searchentry_get_text();
      // next get the text of the node
      gchar *node_text;
      gtk_tree_model_get(model, iter, 0, &node_text,  -1);
      // check if search text is a substring of node_text
      retval = (strstr(node_text, search_text) != NULL);
   }

   return retval;
}

// Callback function if a row is activated
void on_stack_tree_treeview_row_activated(GtkTreeView *tree_view,
                                          GtkTreePath *path,
                                          GtkTreeViewColumn *column,
                                          gpointer user_data) {
   (void) tree_view;
   (void) column;
   (void) user_data;

   // first convert the path of the filtered model
   // into the full tree model
   GtkTreePath *unfiltered_path =
      gtk_tree_model_filter_convert_path_to_child_path(
         GTK_TREE_MODEL_FILTER(stack_tree_treefilter),
         path);
   // extrac the unfiltered path indices
   stack_tree_selected_treepath =
      gtk_tree_path_get_indices_with_depth(
         unfiltered_path,
         &stack_tree_selected_treepath_depth);

#ifdef _DEBUG
   printf("Selected treepath: %d", stack_tree_selected_treepath[0]);
   for (int i=1; i<stack_tree_selected_treepath_depth; i++) {
      printf("->%d", stack_tree_selected_treepath[i]);
   }
   printf("\n");

   vfd_t *vfd_file = NULL;
   vfd_stack_entry_t *vfd_stack = NULL;
   indexed_vfd_trace_and_stack(stack_tree_selected_treepath_depth,
                               stack_tree_selected_treepath,
                               &vfd_file,
                               &vfd_stack);
   if (vfd_file != NULL) {
      printf("selected vfdfile: %s\n", vfd_file->filename);
   }
   if (vfd_stack != NULL) {
      printf("selected Stack: ID=%d, name=%s\n", vfd_stack->ID, vfd_stack->name);
   }
#endif
}
