#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_stack_tree_toolbar.h"
#include "vgtk_stack_tree_searchentry.h"
#include "vgtk_stacktimeline_entry.h"
#include "vfd_types.h"
#include "vfd_stacks.h"
#include "vfd_list.h"

#ifdef _DEBUG
#include "v_timer.h"
#endif

GtkListStore *stack_list_liststore = NULL;
GtkTreeView *stack_list_treeview = NULL;

GtkTreeViewColumn *stack_list_treeview_vfdname_column = NULL;
GtkCellRenderer   *stack_list_treeview_vfdname_text = NULL;
GtkTreeViewColumn *stack_list_treeview_functionname_column = NULL;
GtkCellRenderer   *stack_list_treeview_functionname_text = NULL;
GtkTreeViewColumn *stack_list_treeview_stackID_column = NULL;
GtkCellRenderer   *stack_list_treeview_stackID_text = NULL;
GtkTreeViewColumn *stack_list_treeview_stack_column = NULL;
GtkCellRenderer   *stack_list_treeview_stack_text = NULL;
GtkTreeViewColumn *stack_list_treeview_called_column = NULL;
GtkCellRenderer   *stack_list_treeview_called_text = NULL;
GtkTreeViewColumn *stack_list_treeview_children_called_column = NULL;
GtkCellRenderer   *stack_list_treeview_children_called_text = NULL;
GtkTreeViewColumn *stack_list_treeview_exclusive_time_column = NULL;
GtkCellRenderer   *stack_list_treeview_exclusive_time_text = NULL;
GtkTreeViewColumn *stack_list_treeview_inclusive_time_column = NULL;
GtkCellRenderer   *stack_list_treeview_inclusive_time_text = NULL;

GtkTreeSelection *stack_list_treeselection = NULL;

GtkTreeModelFilter *stack_list_treefilter = NULL;
GtkTreeModelSort *stack_list_treesort = NULL;

gboolean stack_list_determine_visibility(GtkTreeModel *model,
                                         GtkTreeIter *parent,
                                         gpointer data);

void vgtk_build_stack_list_treeview(GtkBuilder *builder) {
   stack_list_liststore = GTK_LIST_STORE(
      gtk_builder_get_object(builder, "stack_list_liststore"));
   stack_list_treeview = GTK_TREE_VIEW(
      gtk_builder_get_object(builder, "stack_list_treeview"));

   stack_list_treeselection = GTK_TREE_SELECTION(
      gtk_builder_get_object(builder, "stack_list_treeselection"));

   stack_list_treefilter = GTK_TREE_MODEL_FILTER(
      gtk_builder_get_object(builder, "stack_list_treefilter"));

   stack_list_treesort = GTK_TREE_MODEL_SORT(
      gtk_builder_get_object(builder, "stack_list_treesort"));

   // vfd-file name column
   stack_list_treeview_vfdname_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_list_treeview_vfdname_column"));
   stack_list_treeview_vfdname_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_list_treeview_vfdname_text"));
   gtk_tree_view_column_add_attribute(stack_list_treeview_vfdname_column,
                                      stack_list_treeview_vfdname_text,
                                      "text", 0);

   // function name column
   stack_list_treeview_functionname_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_list_treeview_functionname_column"));
   stack_list_treeview_functionname_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_list_treeview_functionname_text"));
   gtk_tree_view_column_add_attribute(stack_list_treeview_functionname_column,
                                      stack_list_treeview_functionname_text,
                                      "text", 1);

   // stackID column
   stack_list_treeview_stackID_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_list_treeview_stackID_column"));
   stack_list_treeview_stackID_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_list_treeview_stackID_text"));
   gtk_tree_view_column_add_attribute(stack_list_treeview_stackID_column,
                                      stack_list_treeview_stackID_text,
                                      "text", 2);

   // stack column
   stack_list_treeview_stack_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_list_treeview_stack_column"));
   stack_list_treeview_stack_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_list_treeview_stack_text"));
   gtk_tree_view_column_add_attribute(stack_list_treeview_stack_column,
                                      stack_list_treeview_stack_text,
                                      "text", 3);


   // exclusive stack time column
   stack_list_treeview_exclusive_time_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_list_treeview_exclusive_time_column"));
   stack_list_treeview_exclusive_time_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_list_treeview_exclusive_time_text"));
   gtk_tree_view_column_add_attribute(stack_list_treeview_exclusive_time_column,
                                      stack_list_treeview_exclusive_time_text,
                                      "text", 4);
   gtk_cell_renderer_set_alignment(stack_list_treeview_exclusive_time_text,
                                   1.0, 0.5);

   // inclusive stack time column
   stack_list_treeview_inclusive_time_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_list_treeview_inclusive_time_column"));
   stack_list_treeview_inclusive_time_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_list_treeview_inclusive_time_text"));
   gtk_tree_view_column_add_attribute(stack_list_treeview_inclusive_time_column,
                                      stack_list_treeview_inclusive_time_text,
                                      "text", 5);
   gtk_cell_renderer_set_alignment(stack_list_treeview_inclusive_time_text,
                                   1.0, 0.5);

   // number of stack calls column
   stack_list_treeview_called_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_list_treeview_called_column"));
   stack_list_treeview_called_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_list_treeview_called_text"));
   gtk_tree_view_column_add_attribute(stack_list_treeview_called_column,
                                      stack_list_treeview_called_text,
                                      "text", 6);
   gtk_cell_renderer_set_alignment(stack_list_treeview_called_text,
                                   1.0, 0.5);

   // number of stack call children calls column
   stack_list_treeview_children_called_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(builder, "stack_list_treeview_children_called_column"));
   stack_list_treeview_children_called_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(builder, "stack_list_treeview_children_called_text"));
   gtk_tree_view_column_add_attribute(stack_list_treeview_children_called_column,
                                      stack_list_treeview_children_called_text,
                                      "text", 7);
   gtk_cell_renderer_set_alignment(stack_list_treeview_children_called_text,
                                   1.0, 0.5);

   gtk_tree_model_filter_set_visible_func(
      GTK_TREE_MODEL_FILTER(stack_list_treefilter),
      (GtkTreeModelFilterVisibleFunc) stack_list_determine_visibility,
      NULL, NULL);

   gtk_builder_connect_signals(builder, NULL);

}

void vgtk_stack_list_add_vfdtrace(vfd_t *vfdtrace) {

   // To Prevent Gtk from resorting the list after every entry is added
   // The TreeModel structure is reconnected, such that the View
   // displays the filtered Model and not the filtered and sorted one
   // The ModelSort needs to be completely destroyed.
   gtk_tree_view_set_model(stack_list_treeview, GTK_TREE_MODEL(stack_list_treefilter));
   g_object_unref(stack_list_treesort);

   // loop over all stacks and add them to the list store
   unsigned int nstacks = vfdtrace->header->nstacks;
   // skip istack==0 to avoid init function
   for (unsigned int istack=1; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = vfdtrace->stacks + istack;
      GtkTreeIter iter;
      gtk_list_store_append(stack_list_liststore, &iter);
      gtk_list_store_set(stack_list_liststore, &iter,
                         0, vfdtrace->filename, -1);
      gtk_list_store_set(stack_list_liststore, &iter,
                         1, stack_ptr->name, -1);
      gtk_list_store_set(stack_list_liststore, &iter,
                         2, stack_ptr->ID, -1);
      char *stackstr = get_stack_string(stack_ptr);
      gtk_list_store_set(stack_list_liststore, &iter,
                         3, stackstr, -1);
      free(stackstr);
      gtk_list_store_set(stack_list_liststore, &iter,
                         4, stack_ptr->excl_time, -1);
      gtk_list_store_set(stack_list_liststore, &iter,
                         5, stack_ptr->incl_time, -1);
      gtk_list_store_set(stack_list_liststore, &iter,
                         6, stack_ptr->num_called, -1);
      gtk_list_store_set(stack_list_liststore, &iter,
                         7, stack_ptr->num_calls, -1);
   }

   // Now that everything was added we create a new ModelSort and reconnect it
   // as it was before
   stack_list_treesort = GTK_TREE_MODEL_SORT(
      gtk_tree_model_sort_new_with_model(
         GTK_TREE_MODEL(stack_list_treefilter)));
   gtk_tree_view_set_model(stack_list_treeview, GTK_TREE_MODEL(stack_list_treesort));
}

// reapply the tree filter
void vgtk_stack_list_refilter() {
   gtk_tree_model_filter_refilter(stack_list_treefilter);
}

// Function to determine the visibility of stack tree entries
gboolean stack_list_determine_visibility(GtkTreeModel *model,
                                         GtkTreeIter *iter,
                                         gpointer data) {
   (void) data;

   char *vfdname;
   unsigned int stackID;
   gboolean visible = FALSE;

   gtk_tree_model_get(model, iter,
                      0, &vfdname,
                      2, &stackID,
                      -1);

   vfd_t *vfd_ptr = NULL;
   if (vfdname) {
      // search for the vfd file base on the name
      vfd_ptr = first_vfd();
      while (vfd_ptr != NULL) {
         if (strcmp(vfdname, vfd_ptr->filename) == 0) {
            break;
         }
         vfd_ptr = vfd_ptr->next;
      }
      visible = vfd_ptr->stacks[stackID].visible_in_listview;
   }
   g_free(vfdname);

   return visible;
}

// Callback function if a row is activated
void on_stack_list_treeview_row_activated(GtkTreeView *tree_view,
                                          GtkTreePath *path,
                                          GtkTreeViewColumn *column,
                                          gpointer user_data) {
   (void) tree_view;
   (void) path;
   (void) column;
   (void) user_data;

#ifdef _DEBUG
   printf("Row selected\n");
#endif
}
