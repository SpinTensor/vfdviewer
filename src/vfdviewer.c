#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "paths.h"
#include "vgtk_builder.h"
#include "vgtk_main_window.h"
#include "vfd_list.h"

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


   // remove all remaining vfd traces
   remove_and_free_vfd_list();
   
   return 0;
}
