#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <gtk/gtk.h>

#include "paths.h"
#include "vgtk_builder.h"
#include "vgtk_main_window.h"
#include "vgtk_stack_treeview.h"
#include "vfd_list.h"

int main(int argc, char **argv) {
   printf("init\n");
   char *gladefile = get_gladefile_path(argv[0]);
   printf("gladefile = %s\n", gladefile);

   gtk_init(&argc, &argv);
   vgtk_build_user_interface(gladefile);
   free(gladefile);
   gladefile = NULL;

#ifdef _DEBUG
         fprintf(stderr, "Reading vfd traces from the command line\n");
#endif
   // read in all vfdfiles supplied via the commandline
   for (int iarg=1; iarg<argc; iarg++) {
      if (access(argv[iarg], F_OK) != -1) {
#ifdef _DEBUG
         fprintf(stderr, "Opening File %s\n", argv[iarg]);
#endif
         char *filename = strdup(argv[iarg]);
         vfd_t *vfdfile = new_vfd(filename);
         append_vfd(vfdfile);
         // add the vfdtrace to the stack treeView
         vgtk_stack_tree_add_vfdtrace(vfdfile);
      } else {
         fprintf(stderr, "Unable to locate file %s\n", argv[iarg]);
      }
   }


   vgtk_show_main_window();
   gtk_main();

   // remove all remaining vfd traces
   remove_and_free_vfd_list();
   
   return 0;
}
