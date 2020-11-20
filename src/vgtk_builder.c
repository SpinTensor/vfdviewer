#include <gtk/gtk.h>

#include "vgtk_main_window.h"
#include "vgtk_open_file_dialog.h"
#include "vgtk_main_menu_bar.h"

GtkBuilder *vgtk_builder = NULL;

// build the gtk user interface
void vgtk_build_user_interface(char *gladefile) {
   vgtk_builder = gtk_builder_new_from_file(gladefile);

   // assign the pointer to the main window
   vgtk_main_window = GTK_WINDOW(
      gtk_builder_get_object(vgtk_builder, "main_window"));

   // assign the pointer to the file chooser dialog
   vgtk_open_file_dialog = GTK_FILE_CHOOSER(
      gtk_builder_get_object(vgtk_builder, "open_file_dialog"));

   // connect all callback singals 
   vgtk_connect_main_menu_bar_signals(vgtk_builder);
   gtk_builder_connect_signals(vgtk_builder, NULL);
}
