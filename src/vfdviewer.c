#include <stdlib.h>
#include <stdio.h>

#include "paths.h"

int main(int argc, char **argv) {

   char *gladefile = get_gladefile_path(argv[0]);

   free(gladefile);
   gladefile = NULL;
   return 0;
}
