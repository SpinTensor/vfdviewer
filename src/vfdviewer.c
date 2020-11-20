#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "paths.h"
#include "vgtk_builder.h"
#include "vgtk_main_window.h"

int main(int argc, char **argv) {
   printf("init\n");
   char *gladefile = get_gladefile_path(argv[0]);
   printf("gladefile = %s\n", gladefile);

   gtk_init(&argc, &argv);
   vgtk_build_user_interface(gladefile);
   free(gladefile);
   gladefile = NULL;

   vgtk_show_main_window();
   gtk_main();

   return 0;
}

//// File -> Open
//void on_main_menu_file_menu_open_item_activate(GtkMenuItem *menuitem) {
//   (void) menuitem;
//
//   // show the "Open Text File" dialog box
//   gtk_widget_show(GTK_WIDGET(file_chooser));
//   gboolean opened_file = gtk_dialog_run(GTK_DIALOG(file_chooser));
//   if (opened_file == GTK_RESPONSE_OK) {
//      // get the filenames
//      GSList *selected_files = gtk_file_chooser_get_filenames(file_chooser);
//      int nvfdfiles = g_slist_length(selected_files);
//      // allocate space for vfd files
//      vfdfiles = (vfd_t*) malloc(nvfdfiles*sizeof(vfd_t));
//      for (int ifile=0; ifile<nvfdfiles; ifile++) {
//         GSList *curr_file = g_slist_nth(selected_files, (guint) ifile);
//         vfdfiles[ifile].filename = strdup((char*) curr_file->data);
//         printf("%d %s\n", ifile, vfdfiles[ifile].filename);
//      }
//      // free list memory
//      g_slist_free(g_steal_pointer(&selected_files));
//      for (int ifile=0; ifile<nvfdfiles; ifile++) {
//         read_vfd_file(vfdfiles+ifile);
//      }
//   }
//
//   //Finished opening the file
//   gtk_widget_hide(GTK_WIDGET(file_chooser));
//}
