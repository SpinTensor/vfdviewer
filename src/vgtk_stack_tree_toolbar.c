#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_stack_treeview.h"
#include "vgtk_open_file_dialog.h"
#include "vgtk_stacktimeline_hscrollbar.h"
#include "vgtk_stacktimeline_entry.h"
#include "vfd_list.h"

GtkToolbar *stack_tree_toolbar = NULL;
GtkToolButton *stack_tree_toolbar_expand_button = NULL;
GtkToolButton *stack_tree_toolbar_collapse_button = NULL;
GtkToolButton *stack_tree_toolbar_add_button = NULL;
GtkToolButton *stack_tree_toolbar_remove_button = NULL;

void vgtk_build_stack_tree_toolbar(GtkBuilder *builder) {
   stack_tree_toolbar = GTK_TOOLBAR(
      gtk_builder_get_object(builder, "stack_tree_toolbar"));
   stack_tree_toolbar_expand_button = GTK_TOOL_BUTTON(
      gtk_builder_get_object(builder, "stack_tree_toolbar_expand_button"));
   stack_tree_toolbar_collapse_button = GTK_TOOL_BUTTON(
      gtk_builder_get_object(builder, "stack_tree_toolbar_collapse_button"));
   stack_tree_toolbar_add_button = GTK_TOOL_BUTTON(
      gtk_builder_get_object(builder, "stack_tree_toolbar_add_button"));
   stack_tree_toolbar_remove_button = GTK_TOOL_BUTTON(
      gtk_builder_get_object(builder, "stack_tree_toolbar_remove_button"));

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

// Callback function if add button is clicked
void on_stack_tree_toolbar_add_button_clicked(GtkToolButton *button) {
   (void) button;
   run_open_file_dialog();
}

// Callback function if remove button is clicked
void on_stack_tree_toolbar_remove_button_clicked(GtkToolButton *button) {
   (void) button;
   vfd_t *vfd_trace = get_stack_tree_currently_selected_vfdtrace();
   if (vfd_trace == NULL) {
#ifdef _DEBUG
      fprintf(stderr, "No valid vfd trace selected. Unable to remove it.\n");
#endif
      return;
   } else {
#ifdef _DEBUG
      fprintf(stderr, "Removing vfd trace %s\n", vfd_trace->filename);
#endif
      vgtk_stack_tree_remove_selected_vfdtrace();
      remove_vfd(vfd_trace);
      free_vfd(&vfd_trace);

      // redraw all stacktimelines
      vgtk_redraw_all_stacktimelines();

      vgtk_adjust_main_stacktimeline_hscrollbar();
   }
}
