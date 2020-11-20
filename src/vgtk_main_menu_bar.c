#include <gtk/gtk.h>

#include "vgtk_open_file_dialog.h"
#include "vgtk_main_menu_bar.h"

// Connect main menu bar callback signals
void vgtk_connect_main_menu_bar_signals(GtkBuilder *builder) {
   gtk_builder_connect_signals(builder, NULL);
}

// Callback function to be executed if 
// File->Open is activated
void on_main_menu_file_menu_open_item_activate(GtkMenuItem *menuitem) {
   (void) menuitem;

   // show the "Open Text File" dialog box
   gtk_widget_show(GTK_WIDGET(vgtk_open_file_dialog));
   gboolean opened_file = gtk_dialog_run(GTK_DIALOG(vgtk_open_file_dialog));
   if (opened_file == GTK_RESPONSE_OK) {
      // get the filenames
      GSList *selected_files = gtk_file_chooser_get_filenames(vgtk_open_file_dialog);
      int nvfdfiles = g_slist_length(selected_files);

      // free list memory
      g_slist_free(g_steal_pointer(&selected_files));
   }

   //Finished opening the file
   gtk_widget_hide(GTK_WIDGET(vgtk_open_file_dialog));
//   // show the open file dialog
//   vgtk_show_open_file_dialog();
//   // run the open file logic
//   gint files_opened;
//   files_opened = vgtk_run_open_file_dialog();
//   // If a file was opened the return value is GTK_RESPONSE_OK
//   if (files_opened == GTK_RESPONSE_OK) {
//   } 
//
//   // hide the open file dialog
//   vgtk_hide_open_file_dialog();
}
