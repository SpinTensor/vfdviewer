#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include <stdio.h>

char *get_executable_name(char *argv) {
   char *argv_cpy = strdup(argv);
   return basename(argv_cpy);
}

char *get_base_path(char *argv) {
   char *argv_cpy = strdup(argv);
   char *bin_path = realpath(argv_cpy, NULL);
   free(argv_cpy);
   return dirname(dirname(bin_path));
}

char *get_bin_path(char *argv) {
   char *argv_cpy = strdup(argv);
   char *bin_path = realpath(dirname(argv_cpy), NULL);
   free(argv_cpy);
   return bin_path;
}

char *get_lib_path(char *argv) {
   char *libpostfix = "/lib";
   char *argv_cpy = strdup(argv);
   char *base_path = get_base_path(argv_cpy);
   int lib_path_lenght = strlen(base_path) + strlen(libpostfix) + 1;
   char *lib_path = (char*) malloc(lib_path_lenght*sizeof(char));
   strcpy(lib_path, base_path);
   strcat(lib_path, libpostfix);
   free(argv_cpy);
   free(base_path);
   return lib_path;
}

char *get_include_path(char *argv) {
   char *includepostfix = "/include";
   char *argv_cpy = strdup(argv);
   char *base_path = get_base_path(argv_cpy);
   int include_path_lenght = strlen(base_path) + strlen(includepostfix) + 1;
   char *include_path = (char*) malloc(include_path_lenght*sizeof(char));
   strcpy(include_path, base_path);
   strcat(include_path, includepostfix);
   free(argv_cpy);
   free(base_path);
   return include_path;
}

char *get_shared_path(char *argv) {
   char *sharedpostfix = "/shared";
   char *argv_cpy = strdup(argv);
   char *base_path = get_base_path(argv_cpy);
   int shared_path_lenght = strlen(base_path) + strlen(sharedpostfix) + 1;
   char *shared_path = (char*) malloc(shared_path_lenght*sizeof(char));
   strcpy(shared_path, base_path);
   strcat(shared_path, sharedpostfix);
   free(argv_cpy);
   free(base_path);
   return shared_path;
}

char *get_gladefile_path(char *argv) {
   char *dirseparator = "/";
   char *glade_extension = ".glade";
   char *sharedpath = get_shared_path(argv);
   char *executable_name = get_executable_name(argv);
   int glade_path_length = strlen(sharedpath) + strlen(dirseparator) +
                           strlen(executable_name) + 
                           strlen(glade_extension) + 1;
   char *gladefile_path = (char*) malloc(glade_path_length*sizeof(char));
   strcpy(gladefile_path, sharedpath);
   strcat(gladefile_path, dirseparator);
   strcat(gladefile_path, executable_name);
   strcat(gladefile_path, glade_extension);
   free(sharedpath);
   sharedpath = NULL;
   free(executable_name);
   executable_name = NULL;
   return gladefile_path;
}
