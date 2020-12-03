#include <gtk/gtk.h>

#include "vfd_types.h"
#include "vfd_list.h"
#include "vgtk_stack_treeview.h"
#include "vgtk_stacktimeline_entry.h"

GtkFileChooser *vgtk_open_file_dialog = NULL;

void vgtk_build_open_file_dialog(GtkBuilder *builder) {
   vgtk_open_file_dialog = GTK_FILE_CHOOSER(
      gtk_builder_get_object(builder, "open_file_dialog"));
   gtk_builder_connect_signals(builder, NULL);
}

void run_open_file_dialog() {
   printf("running open dialog\n");
   // show the open file dialog
   gtk_widget_show(GTK_WIDGET(vgtk_open_file_dialog));
   // run the open file logic
   gint files_to_open = gtk_dialog_run(GTK_DIALOG(vgtk_open_file_dialog));
   // If a file was opened the return value is GTK_RESPONSE_OK
   if (files_to_open == GTK_RESPONSE_OK) {
      // get the filenames
      GSList *selected_files = gtk_file_chooser_get_filenames(vgtk_open_file_dialog);
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

         // add the vfdtrace to the stack treeView
         vgtk_stack_tree_add_vfdtrace(vfdfile);
         // add the vfdtrace to the timeline view
         init_stacktimeline_entry(vfdfile);
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
   gtk_widget_hide(GTK_WIDGET(vgtk_open_file_dialog));
}
