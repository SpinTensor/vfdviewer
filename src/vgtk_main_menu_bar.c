#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_open_file_dialog.h"
#include "vgtk_main_menu_bar.h"
#include "vfd_list.h"

// Connect main menu bar callback signals
void vgtk_connect_main_menu_bar_signals(GtkBuilder *builder) {
   gtk_builder_connect_signals(builder, NULL);
}

// Callback function to be executed if 
// File->Open is activated
void on_main_menu_file_menu_open_item_activate(GtkMenuItem *menuitem) {
   (void) menuitem;

   // show the open file dialog
   vgtk_show_open_file_dialog();
   // run the open file logic
   gint files_to_open = vgtk_run_open_file_dialog();
   // If a file was opened the return value is GTK_RESPONSE_OK
   if (files_to_open == GTK_RESPONSE_OK) {
      // get the filenames
      GSList *selected_files = vgtk_open_file_dialog_get_filenames();
      int nfiles = g_slist_length(selected_files);
      // go through the filenames and open them
      for (int ifile=0; ifile<nfiles; ifile++) {
         GSList *curr_file = g_slist_nth(selected_files, (guint) ifile);
         char *filename = strdup((char*) curr_file->data);
#ifdef _DEBUG
         fprintf(stderr, "Loading vfd-file: %s\n", filename);
#endif
         vfd_t *vfdfile = new_vfd(filename);
         append_vfd(vfdfile);
      }
      // free list memory
      g_slist_free(g_steal_pointer(&selected_files));
   } 

#ifdef _DEBUG
   {
      fprintf(stderr, "Currently loaded vfdfiles are:\n");
      int n = num_vfds();
      for (int i=0; i<n; i++) {
         vfd_t *tmpvfd = nth_vfd(i);
         fprintf(stderr, "   %d: %s\n", i, tmpvfd->filename);
      }
   }
#endif

   // hide the open file dialog
   vgtk_hide_open_file_dialog();
}
