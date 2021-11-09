#include <stdlib.h>
#include <stdio.h>

#include "vfd_types.h"

void read_vfd_hwc_header(FILE *vfd_file, vfd_hwc_header_t **hwc_header_ptr) {
   *hwc_header_ptr = (vfd_hwc_header_t*) malloc(sizeof(vfd_hwc_header_t));
   vfd_hwc_header_t *hwc_header = *hwc_header_ptr;

   size_t read_elem;
   read_elem = fread(&(hwc_header->n_formulae), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading hwc-header n_formulae\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   read_elem = fread(&(hwc_header->n_hw_obs), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading hwc-header n_hw_obs\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   if (hwc_header->n_hw_obs > 0) {
      // add one hardware observable for the cycletime
      hwc_header->n_hw_obs++;

      hwc_header->hw_obs_names =
         (char**) malloc(hwc_header->n_hw_obs*sizeof(char*));
      hwc_header->te_var_names =
         (char**) malloc(hwc_header->n_hw_obs*sizeof(char*));
      for (int i_hw_obs=0; i_hw_obs<hwc_header->n_hw_obs-1; i_hw_obs++) {
         int length = 0;
         // reading the Hardware counter name
         read_elem = fread(&length, sizeof(int), 1, vfd_file);
         if (read_elem != 1) {
            fprintf(stderr, "Error in reading string length in hwc-header "
                            "HWC name %d\n"
                            "Expected 1 int, read %ld\n",
                            i_hw_obs, read_elem);
            exit(EXIT_FAILURE);
         }
         hwc_header->hw_obs_names[i_hw_obs] = (char*) malloc(length*sizeof(char));
         read_elem = fread(hwc_header->hw_obs_names[i_hw_obs],
                           sizeof(char), length, vfd_file);
         if (read_elem != (size_t) length) {
            fprintf(stderr, "Error in reading hwc-header HWC name\n"
                            "Expected %d chars, read %ld\n",
                            length, read_elem);
            exit(EXIT_FAILURE);
         }
   
         // reading the tiny expression variable name
         read_elem = fread(&length, sizeof(int), 1, vfd_file);
         if (read_elem != 1) {
            fprintf(stderr, "Error in reading string length in hwc-header "
                            "TinyExpression name %d\n"
                            "Expected 1 int, read %ld\n",
                            i_hw_obs, read_elem);
            exit(EXIT_FAILURE);
         }
         hwc_header->te_var_names[i_hw_obs] = (char*) malloc(length*sizeof(char));
         read_elem = fread(hwc_header->te_var_names[i_hw_obs],
                           sizeof(char), length, vfd_file);
         if (read_elem != (size_t) length) {
            fprintf(stderr, "Error in reading hwc-header TinyExpression name\n"
                            "Expected %d chars, read %ld\n",
                            length, read_elem);
            exit(EXIT_FAILURE);
         }
   
      }

      // add the cycletime observable by hand
      int i_hw_obs = hwc_header->n_hw_obs-1;
      hwc_header->hw_obs_names[i_hw_obs] = strdup("Cycletime");
      hwc_header->te_var_names[i_hw_obs] = strdup("cycletime");
   }

   if (hwc_header->n_formulae > 0) {
      hwc_header->scen_expr_names =
         (char**) malloc(hwc_header->n_formulae*sizeof(char*));
      hwc_header->scen_expr_formulae =
         (char**) malloc(hwc_header->n_formulae*sizeof(char*));
      hwc_header->scen_expr_integrated =
         (bool*) malloc(hwc_header->n_formulae*sizeof(bool));
      for (int i_formula=0; i_formula<hwc_header->n_formulae; i_formula++) {
         int length = 0;
         // reading the scenario expression name
         read_elem = fread(&length, sizeof(int), 1, vfd_file);
         if (read_elem != 1) {
            fprintf(stderr, "Error in reading string length in hwc-header "
                            "scenario expression name %d\n"
                            "Expected 1 int, read %ld\n",
                            i_formula, read_elem);
            exit(EXIT_FAILURE);
         }
         hwc_header->scen_expr_names[i_formula] = (char*) malloc(length*sizeof(char));
         read_elem = fread(hwc_header->scen_expr_names[i_formula],
                           sizeof(char), length, vfd_file);
         if (read_elem != (size_t) length) {
            fprintf(stderr, "Error in reading hwc-header scenario expression name\n"
                            "Expected %d chars, read %ld\n",
                            length, read_elem);
            exit(EXIT_FAILURE);
         }
   
         // reading the scenario expression formula
         read_elem = fread(&length, sizeof(int), 1, vfd_file);
         if (read_elem != 1) {
            fprintf(stderr, "Error in reading string length in hwc-header "
                            "scenario expression formula %d\n"
                            "Expected 1 int, read %ld\n",
                            i_formula, read_elem);
            exit(EXIT_FAILURE);
         }
   
         hwc_header->scen_expr_formulae[i_formula] = (char*) malloc(length*sizeof(char));
         read_elem = fread(hwc_header->scen_expr_formulae[i_formula],
                           sizeof(char), length, vfd_file);
         if (read_elem != (size_t) length) {
            fprintf(stderr, "Error in reading hwc-header scenario expression formula\n"
                            "Expected %d chars, read %ld\n",
                            length, read_elem);
            exit(EXIT_FAILURE);
         }
   
         // read the scenario expression integrated property
         read_elem = fread(hwc_header->scen_expr_integrated+i_formula,
                           sizeof(bool), 1, vfd_file);
         if (read_elem != 1) {
            fprintf(stderr, "Error in reading hwc-header scenario integrated property\n"
                            "Expected 1 bool, read %ld\n",
                            read_elem);
            exit(EXIT_FAILURE);
         }
      }
   }
}

void free_vfd_hwc_header(vfd_hwc_header_t *hwc_header) {
   if (hwc_header->n_hw_obs > 0) {
      for (int i_hw_obs=0; i_hw_obs<hwc_header->n_hw_obs; i_hw_obs++) {
         free(hwc_header->hw_obs_names[i_hw_obs]);
         hwc_header->hw_obs_names[i_hw_obs] = NULL;
         free(hwc_header->te_var_names[i_hw_obs]);
         hwc_header->te_var_names[i_hw_obs] = NULL;
      }
      free(hwc_header->hw_obs_names);
      hwc_header->hw_obs_names = NULL;
      free(hwc_header->te_var_names);
      hwc_header->te_var_names = NULL;
      hwc_header->n_hw_obs = 0;
   }

   if (hwc_header->n_formulae) {
      for (int i_formula=0; i_formula<hwc_header->n_formulae; i_formula++) {
         free(hwc_header->scen_expr_names[i_formula]);
         hwc_header->scen_expr_names[i_formula] = NULL;
         free(hwc_header->scen_expr_formulae[i_formula]);
         hwc_header->scen_expr_formulae[i_formula] = NULL;
      }
      free(hwc_header->scen_expr_names);
      hwc_header->scen_expr_names = NULL;
      free(hwc_header->scen_expr_formulae);
      hwc_header->scen_expr_formulae = NULL;
      free(hwc_header->scen_expr_integrated);
      hwc_header->scen_expr_integrated = NULL;
      hwc_header->n_formulae = 0;
   }

   free(hwc_header);
}

void print_vfd_hwc_header(vfd_hwc_header_t *hwc_header) {
   fprintf(stderr, "VFD-HWCs:\n");
   fprintf(stderr, "   Number of HW counters: %d\n", hwc_header->n_hw_obs);
   for (int i_hw_obs=0; i_hw_obs<hwc_header->n_hw_obs; i_hw_obs++) {
      fprintf(stderr, "      %s (%s)\n",
              hwc_header->hw_obs_names[i_hw_obs],
              hwc_header->te_var_names[i_hw_obs]);
   }
   fprintf(stderr, "   Number of Formulae: %d\n", hwc_header->n_formulae);
   for (int i_formula=0; i_formula<hwc_header->n_formulae; i_formula++) {
      fprintf(stderr, "      (%s): %s = %s\n",
              hwc_header->scen_expr_integrated ? "int" : "dif",
              hwc_header->scen_expr_names[i_formula],
              hwc_header->scen_expr_formulae[i_formula]);
   }
   fprintf(stderr, "\n");
}
