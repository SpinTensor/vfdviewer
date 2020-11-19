#include <stdlib.h>
#include <stdio.h>

#include "vfd_types.h"
#include "vfd_header_IO.h"

void read_vfd_header(FILE *vfd_file, vfd_header_t **header_ptr) {
   *header_ptr = (vfd_header_t*) malloc(sizeof(vfd_header_t));
   vfd_header_t *header = *header_ptr;

   size_t read_elem;

   read_elem = fread(&(header->vfd_version), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header vfd_version\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   read_elem = fread(&(header->vftrace_version), sizeof(char), VFTR_VERSIONSIZE, vfd_file);
   if (read_elem != VFTR_VERSIONSIZE) {
      fprintf(stderr, "Error in reading vfd-header vftrace_version\n"
                      "Expected %d char, read %ld\n",
                      VFTR_VERSIONSIZE, read_elem);
      exit(EXIT_FAILURE);
   }
   header->vftrace_version[VFTR_VERSIONSIZE] = '\0';

   read_elem = fread(&(header->date), sizeof(char), DATESTRINGSIZE, vfd_file);
   if (read_elem != DATESTRINGSIZE) {
      fprintf(stderr, "Error in reading vfd-header date\n"
                      "Expected %d char, read %ld\n",
                      DATESTRINGSIZE, read_elem);
      exit(EXIT_FAILURE);
   }
   header->date[DATESTRINGSIZE] = '\0';

   read_elem = fread(&(header->interval), sizeof(long long), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header interva\n"
                      "Expected 1 long long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   read_elem = fread(&(header->nthreads), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header nthreads\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   read_elem = fread(&(header->mythread), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header mythread\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   read_elem = fread(&(header->nranks), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header nranks\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(header->myrank), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header myrank\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(header->runtime), sizeof(double), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header runtime\n"
                      "Expected 1 double, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(header->function_samplecount), sizeof(unsigned int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header function_samplecount\n"
                      "Expected 1 unsigned int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(header->message_samplecount), sizeof(unsigned int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header message_samplecount\n"
                      "Expected 1 unsigned int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(header->stackscount), sizeof(unsigned int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header stackscount\n"
                      "Expected 1 unsigned int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(header->stacksoffset), sizeof(long), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header stacksoffset\n"
                      "Expected 1 long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(header->sampleoffset), sizeof(long), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header sampleoffset\n"
                      "Expected 1 long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
}

void print_vfd_header(vfd_header_t *vfd_header) {

   fprintf(stderr, "VFD-Header:\n");
   fprintf(stderr, "   vfd version:     %d\n", vfd_header->vfd_version);
   fprintf(stderr, "   vftrace version: %s\n", vfd_header->vftrace_version);
   fprintf(stderr, "   Date:            %s\n", vfd_header->date);
   fprintf(stderr, "   MPI rank         %d (of %d)\n", vfd_header->myrank,
                                                       vfd_header->nranks);
   fprintf(stderr, "   OMP thread       %d (of %d)\n", vfd_header->mythread,
                                                       vfd_header->nthreads);
   fprintf(stderr, "   Sample interval: %.6le seconds\n", vfd_header->interval*1.0e-6);
   fprintf(stderr, "   Runtime:         %.3lf seconds\n", vfd_header->runtime);
   fprintf(stderr, "   Samples:         %d\n", vfd_header->function_samplecount + 
                                               vfd_header->message_samplecount);
   fprintf(stderr, "      Function:     %d\n", vfd_header->function_samplecount);
   fprintf(stderr, "      Messages:     %d\n", vfd_header->message_samplecount);
   fprintf(stderr, "   Stacks:          %u\n", vfd_header->stackscount);
   fprintf(stderr, "   Stacks offset:   0x%lx\n", vfd_header->stacksoffset);
   fprintf(stderr, "   Sample offset:   0x%lx\n", vfd_header->sampleoffset);
   fprintf(stderr, "\n");
}
