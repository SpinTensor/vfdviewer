#include <gtk/gtk.h>

#include "vgtk_main_window.h"
#include "vgtk_open_file_dialog.h"
#include "vgtk_about_dialog.h"
#include "vgtk_main_menu_bar.h"
#include "vgtk_stack_treeview.h"

GtkBuilder *vgtk_builder = NULL;

// build the gtk user interface
void vgtk_build_user_interface(char *gladefile) {
   vgtk_builder = gtk_builder_new_from_file(gladefile);

   // assign the pointer to the main window
   vgtk_build_main_window(vgtk_builder);

   // assign the pointer to the file chooser dialog
   vgtk_open_file_dialog = GTK_FILE_CHOOSER(
      gtk_builder_get_object(vgtk_builder, "open_file_dialog"));

   // assign the pointer to the about dialog
   vgtk_about_dialog = GTK_ABOUT_DIALOG(
      gtk_builder_get_object(vgtk_builder, "about_dialog"));

   // assign the pointers for handling the stack_treeStore
   stack_tree_treestore = GTK_TREE_STORE(
      gtk_builder_get_object(vgtk_builder, "stack_tree_treestore"));
   stack_tree_treeview = GTK_TREE_VIEW(
      gtk_builder_get_object(vgtk_builder, "stack_tree_treeview"));
   stack_tree_treeview_functionnames_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(vgtk_builder, "stack_tree_treeview_functionnames_column"));
   stack_tree_treeview_functionnames_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(vgtk_builder, "stack_tree_treeview_functionnames_text"));
   stack_tree_treeview_stackID_column = GTK_TREE_VIEW_COLUMN(
      gtk_builder_get_object(vgtk_builder, "stack_tree_treeview_stackID_column"));
   stack_tree_treeview_stackID_text = GTK_CELL_RENDERER(
      gtk_builder_get_object(vgtk_builder, "stack_tree_treeview_stackID_text"));
   stack_tree_treeselection = GTK_TREE_SELECTION(
      gtk_builder_get_object(vgtk_builder, "stack_tree_treeselection"));

   gtk_tree_view_column_add_attribute(stack_tree_treeview_functionnames_column,
                                      stack_tree_treeview_functionnames_text,
                                      "text", 0);
   gtk_tree_view_column_add_attribute(stack_tree_treeview_stackID_column,
                                      stack_tree_treeview_stackID_text,
                                      "text", 0);

   // connect all callback singals 
   vgtk_connect_main_menu_bar_signals(vgtk_builder);
   vgtk_connect_about_dialog_signals(vgtk_builder);
   vgtk_connect_stack_treeview(vgtk_builder);
   gtk_builder_connect_signals(vgtk_builder, NULL);
}
