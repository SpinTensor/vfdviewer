#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_main_window.h"
#include "vgtk_open_file_dialog.h"
#include "vgtk_about_dialog.h"
#include "vgtk_main_menu_bar.h"
#include "vgtk_stack_treeview.h"
#include "vgtk_main_view.h"

GtkBuilder *vgtk_builder = NULL;

// build the gtk user interface
void vgtk_build_user_interface() {
   // _DATADIR is fed in throught -D_DATADIR=...
   // This two layer stringify is needed to make it into
   // a literal string that can be combined with the
   // glade filename
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)
   char *gladefile = STRINGIFY(_DATADIR) "/vfdviewer.glade";
#undef STRINGIFY
#undef STRINGIFY_

   if (access(gladefile, F_OK) != -1) {
#ifdef _DEBUG
   fprintf(stderr, "Opening GTK-builder file: \"%s\"\n", gladefile);
#endif
      vgtk_builder = gtk_builder_new_from_file(gladefile);
   } else {
      fprintf(stderr, "Unable to locale GTK-builder file\n");
      fprintf(stderr, "Expected location: \"%s\"\n", gladefile);
      exit(EXIT_FAILURE);
   }

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

   // build main viewer area
   vgtk_build_main_view(vgtk_builder);

   // connect all callback singals
   gtk_builder_connect_signals(vgtk_builder, NULL);
}
