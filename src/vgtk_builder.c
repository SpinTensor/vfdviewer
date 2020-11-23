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

   // assign the pointer to the main menu bar
   vgtk_build_main_menu_bar(vgtk_builder);

   // assign the pointer to the file chooser dialog
   vgtk_build_open_file_dialog(vgtk_builder);

   // assign the pointer to the about dialog
   vgtk_build_about_dialog(vgtk_builder);

   // assign the pointers for handling the stack_treeStore
   vgtk_build_stack_treeview(vgtk_builder);

   // connect all callback singals 
   gtk_builder_connect_signals(vgtk_builder, NULL);
}
