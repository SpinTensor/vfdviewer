#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "paths.h"
#include "vfd_IO.h"

GtkBuilder *builder;
GtkWindow *window;
GtkFileChooser *file_chooser;

int nvfdfiles = 0;
vfd_t *vfdfiles = NULL;

int main(int argc, char **argv) {
   printf("init\n");
   char *gladefile = get_gladefile_path(argv[0]);
   printf("gladefile = %s\n", gladefile);

//   FILE *vfd_file = fopen("test.vfd", "r");
//   read_vfd_file(vfd_file);
//   fclose(vfd_file);

   gtk_init(&argc, &argv);

   builder = gtk_builder_new_from_file(gladefile);
   free(gladefile);
   gladefile = NULL;

   window = GTK_WINDOW(gtk_builder_get_object(builder, "main_window"));
   file_chooser = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "filechooser_window"));

   gtk_builder_connect_signals(builder, NULL);

   gtk_widget_show(GTK_WIDGET(window));
   gtk_main();

   return 0;
}

// File -> Open
void on_main_menu_file_menu_open_item_activate(GtkMenuItem *menuitem) {
   (void) menuitem;

   // show the "Open Text File" dialog box
   gtk_widget_show(GTK_WIDGET(file_chooser));
   gboolean opened_file = gtk_dialog_run(GTK_DIALOG(file_chooser));
   if (opened_file == GTK_RESPONSE_OK) {
      // get the filenames
      GSList *selected_files = gtk_file_chooser_get_filenames(file_chooser);
      int nvfdfiles = g_slist_length(selected_files);
      // allocate space for vfd files
      vfdfiles = (vfd_t*) malloc(nvfdfiles*sizeof(vfd_t));
      for (int ifile=0; ifile<nvfdfiles; ifile++) {
         GSList *curr_file = g_slist_nth(selected_files, (guint) ifile);
         vfdfiles[ifile].filename = strdup((char*) curr_file->data);
         printf("%d %s\n", ifile, vfdfiles[ifile].filename);
      }
      // free list memory
      g_slist_free(g_steal_pointer(&selected_files));
      for (int ifile=0; ifile<nvfdfiles; ifile++) {
         read_vfd_file(vfdfiles+ifile);
      }
   }

   //Finished opening the file
   gtk_widget_hide(GTK_WIDGET(file_chooser));
}
