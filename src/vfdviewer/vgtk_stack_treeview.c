#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_stack_tree_toolbar.h"
#include "vgtk_stack_tree_searchentry.h"
#include "vgtk_stacktimeline_entry.h"
#include "vfd_types.h"
#include "vfd_list.h"

#ifdef _DEBUG
#include "v_timer.h"
#endif

GtkTreeStore *stack_tree_treestore = NULL;
GtkTreeView *stack_tree_treeview = NULL;

GtkTreeViewColumn *stack_tree_treeview_functionnames_column = NULL;
GtkCellRenderer   *stack_tree_treeview_functionnames_text = NULL;
GtkTreeViewColumn *stack_tree_treeview_called_column = NULL;
GtkCellRenderer   *stack_tree_treeview_called_text = NULL;
GtkTreeViewColumn *stack_tree_treeview_children_called_column = NULL;
GtkCellRenderer   *stack_tree_treeview_children_called_text = NULL;
GtkTreeViewColumn *stack_tree_treeview_exclusive_time_column = NULL;
GtkCellRenderer   *stack_tree_treeview_exclusive_time_text = NULL;
GtkTreeViewColumn *stack_tree_treeview_inclusive_time_column = NULL;
GtkCellRenderer   *stack_tree_treeview_inclusive_time_text = NULL;

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

   stack_tree_treeselection = GTK_TREE_SELECTION(
      gtk_builder_get_object(builder, "stack_tree_treeselection"));

   stack_tree_treefilter = GTK_TREE_MODEL_FILTER(
      gtk_builder_get_object(builder, "stack_tree_treefilter"));

   // function name column
   stack_tree_treeview_functionnames_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_tree_treeview_functionnames_column"));
   stack_tree_treeview_functionnames_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_tree_treeview_functionnames_text"));
   gtk_tree_view_column_add_attribute(stack_tree_treeview_functionnames_column,
                                      stack_tree_treeview_functionnames_text,
                                      "text", 0);

   // exclusive stack time column
   stack_tree_treeview_exclusive_time_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_tree_treeview_exclusive_time_column"));
   stack_tree_treeview_exclusive_time_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_tree_treeview_exclusive_time_text"));
   gtk_tree_view_column_add_attribute(stack_tree_treeview_exclusive_time_column,
                                      stack_tree_treeview_exclusive_time_text,
                                      "text", 1);
   gtk_cell_renderer_set_alignment(stack_tree_treeview_exclusive_time_text,
                                   1.0, 0.5);

   // inclusive stack time column
   stack_tree_treeview_inclusive_time_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_tree_treeview_inclusive_time_column"));
   stack_tree_treeview_inclusive_time_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_tree_treeview_inclusive_time_text"));
   gtk_tree_view_column_add_attribute(stack_tree_treeview_inclusive_time_column,
                                      stack_tree_treeview_inclusive_time_text,
                                      "text", 2);
   gtk_cell_renderer_set_alignment(stack_tree_treeview_inclusive_time_text,
                                   1.0, 0.5);

   // number of stack calls column
   stack_tree_treeview_called_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_tree_treeview_called_column"));
   stack_tree_treeview_called_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_tree_treeview_called_text"));
   gtk_tree_view_column_add_attribute(stack_tree_treeview_called_column,
                                      stack_tree_treeview_called_text,
                                      "text", 3);
   gtk_cell_renderer_set_alignment(stack_tree_treeview_called_text,
                                   1.0, 0.5);

   // number of stack call children calls column
   stack_tree_treeview_children_called_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_tree_treeview_children_called_column"));
   stack_tree_treeview_children_called_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_tree_treeview_children_called_text"));
   gtk_tree_view_column_add_attribute(stack_tree_treeview_children_called_column,
                                      stack_tree_treeview_children_called_text,
                                      "text", 4);
   gtk_cell_renderer_set_alignment(stack_tree_treeview_children_called_text,
                                   1.0, 0.5);

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
   gtk_tree_store_set(stack_tree_treestore, &iter,
                      1, stacklevel->excl_time, -1);
   gtk_tree_store_set(stack_tree_treestore, &iter,
                      2, stacklevel->incl_time, -1);
   gtk_tree_store_set(stack_tree_treestore, &iter,
                      3, stacklevel->num_called, -1);
   gtk_tree_store_set(stack_tree_treestore, &iter,
                      4, stacklevel->num_calls, -1);

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
   gtk_tree_store_set(stack_tree_treestore, &iter,
                      1, vfdtrace->header->runtime, -1);
   gtk_tree_store_set(stack_tree_treestore, &iter,
                      2, vfdtrace->header->runtime, -1);
   gtk_tree_store_set(stack_tree_treestore, &iter,
                      3, 1, -1);
   gtk_tree_store_set(stack_tree_treestore, &iter,
                      4, 1, -1);

   // add all stack entries recursively
   // skip init as it has no additional information
   for (int icallee=1; icallee<vfdtrace->stacks->ncallees; icallee++) {
      vgtk_stack_tree_add_level(&iter, vfdtrace->stacks->callees[icallee]);
   }
}

void vgtk_stack_tree_remove_level(GtkTreeModel *model, GtkTreeIter *iter) {
   // Check if the iter has child iters
#ifdef _DEBUG
   GtkTreePath *path = gtk_tree_model_get_path (model, iter);
   fprintf(stderr, "   removing tree entry %s\n", gtk_tree_path_to_string(path));
   gtk_tree_path_free(path);
#endif

   while (gtk_tree_model_iter_has_child(model, iter)) {
      gint nchildren = gtk_tree_model_iter_n_children(model, iter);
      // iterate over the children in reverse
      // and remove them
      GtkTreeIter child_iter;
      gtk_tree_model_iter_nth_child(model,
                                    &child_iter,
                                    iter,
                                    nchildren-1);
      // call this function recuresively
      vgtk_stack_tree_remove_level(model, &child_iter);
   }
   // remove the iter
   gtk_tree_store_remove(GTK_TREE_STORE(model), iter);
}

void vgtk_stack_tree_remove_selected_vfdtrace() {
   if (stack_tree_selected_treepath_depth == 1) {
      GtkTreePath *path = gtk_tree_path_new_from_indicesv(
         stack_tree_selected_treepath,
         stack_tree_selected_treepath_depth);
      GtkTreeIter iter;
      gtk_tree_model_get_iter(GTK_TREE_MODEL(stack_tree_treestore),
                              &iter,
                              path);

      // remove the entry as well as all its children
      vgtk_stack_tree_remove_level(GTK_TREE_MODEL(stack_tree_treestore), &iter);

      // unselect everything
      gtk_tree_selection_unselect_all(stack_tree_treeselection);
      stack_tree_selected_treepath_depth = 0;
      stack_tree_selected_treepath = NULL;
   }
}

vfd_t *get_stack_tree_currently_selected_vfdtrace() {
   // first get information
   // if any node in the tree is selected
   gboolean has_selected_row;
   GtkTreeIter iter;
   GtkTreeModel *tmpmodel = GTK_TREE_MODEL(stack_tree_treefilter);
   has_selected_row = gtk_tree_selection_get_selected(
      stack_tree_treeselection,
      &tmpmodel,
      &iter);
   // if no tree node is selected terminate
   if (!has_selected_row) {
      return NULL;
   }
   // get the path iter points to
   GtkTreePath *path;
   path = gtk_tree_model_get_path(
      tmpmodel, &iter);

   // convert the path to a sequence of indices
   gint path_depth = 0;
   gint *path_indices =
      gtk_tree_path_get_indices_with_depth(
         path,
         &path_depth);

   // continue only if the vfd entry is selected,
   // no subnode and not nothing
   if (path_depth != 1) {
      return NULL;
   }
   // get the corresponding vfd trace and stack entry
   vfd_t *vfd_file = nth_vfd(path_indices[0]);

   gtk_tree_path_free(path);
   path = NULL;

   return vfd_file;
}

// reapply the tree filter
void vgtk_stack_tree_refilter() {
   gtk_tree_model_filter_refilter(stack_tree_treefilter);

   // redraw stacktimelines (for highlighting selected stacks)
   vgtk_redraw_all_stacktimelines();
}

// select a filtered tree entry based on a unfiltered index list
void stack_tree_select_entry_from_indices(int nidx, int *indices) {
   // make it into a path for the unfiltered model
   GtkTreePath *unfiltered_path = gtk_tree_path_new_from_indicesv(indices, nidx);

   // convert the unfiltered path to the filtered one
   GtkTreePath *filtered_path =
      gtk_tree_model_filter_convert_child_path_to_path(
         stack_tree_treefilter, unfiltered_path);


   gtk_tree_selection_select_path(stack_tree_treeselection, unfiltered_path);

   gtk_tree_path_free(unfiltered_path);
   gtk_tree_path_free(filtered_path);
}

// Function to determine the visibility of stack tree entries
gboolean stack_tree_determine_visibility(GtkTreeModel *model,
                                         GtkTreeIter *iter,
                                         gpointer data) {
   (void) data;
   // visibility was precomputed by the search entry changed signal
   // Here only a simple lookup is needed.

   // Get the path iter is pointing to
   GtkTreePath *path =
      gtk_tree_model_get_path(
         model, iter);

   // convert the path to a sequence of indices
   gint path_depth = 0;
   gint *path_indices =
      gtk_tree_path_get_indices_with_depth(
         path,
         &path_depth);

   // get the corresponding vfd trace and stack entry
   vfd_t *vfd_file = NULL;
   vfd_stack_entry_t *vfd_stack = NULL;
   indexed_vfd_trace_and_stack((int) path_depth,
                               (int*) path_indices,
                               &vfd_file,
                               &vfd_stack);

#ifdef _DEBUG
//   fprintf(stderr, "Updating visibility for %s", vfd_file->filename);
//   for (int i=1; i<path_depth; i++) {
//      fprintf(stderr, ":%d", path_indices[i]);
//   }
//   fprintf(stderr, "\n");
#endif

   // free the newly created path
   gtk_tree_path_free(path);
   path = NULL;
   if (path_depth == 1) {
      return vfd_file->stacks[0].visible_in_treeview;
   } else {
      return vfd_stack->visible_in_treeview;
   }
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
   fprintf(stderr, "Activated treepath: %d", stack_tree_selected_treepath[0]);
   for (int i=1; i<stack_tree_selected_treepath_depth; i++) {
      fprintf(stderr, "->%d", stack_tree_selected_treepath[i]);
   }
   fprintf(stderr, "\n");

   vfd_t *vfd_file = NULL;
   vfd_stack_entry_t *vfd_stack = NULL;
   indexed_vfd_trace_and_stack(stack_tree_selected_treepath_depth,
                               stack_tree_selected_treepath,
                               &vfd_file,
                               &vfd_stack);
   if (vfd_file != NULL) {
      fprintf(stderr, "Activated vfdfile: %s\n", vfd_file->filename);
   }
   if (vfd_stack != NULL) {
      fprintf(stderr, "Activated Stack: ID=%d, name=%s\n", vfd_stack->ID, vfd_stack->name);
   }
#endif
}
