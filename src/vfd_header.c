#include <stdlib.h>
#include <stdio.h>

#include "vfd_types.h"
#include "vfd_header.h"

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

   int package_string_len;
   read_elem = fread(&package_string_len, sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
       fprintf(stderr, "Error in reading vfd-header package_string_len\n"
                       "Expected 1 int, read %ld\n",
                       read_elem);
       exit(EXIT_FAILURE);
   }
   header->package_string = (char*) malloc(package_string_len*sizeof(char));
   read_elem = fread(header->package_string, sizeof(char), package_string_len, vfd_file);
   if (read_elem != (size_t)package_string_len) {
      fprintf(stderr, "Error in reading vfd-header package_string\n"
                      "Expected %d char, read %ld\n",
                      package_string_len, read_elem);
      exit(EXIT_FAILURE);
   }

   int datestr_len;
   read_elem = fread(&datestr_len, sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header datestr_len\n"
                      "Expected %d int, read %ld\n",
                      datestr_len, read_elem);
      exit(EXIT_FAILURE);
   }
   header->datestr_start = (char*) malloc(datestr_len*sizeof(char));
   read_elem = fread(header->datestr_start, sizeof(char), datestr_len, vfd_file);
   if (read_elem != (size_t)datestr_len) {
      fprintf(stderr, "Error in reading vfd-header start date\n"
                      "Expected %d char, read %ld\n",
                      datestr_len, read_elem);
      exit(EXIT_FAILURE);
   }
   header->datestr_end = (char*) malloc(datestr_len*sizeof(char));
   read_elem = fread(header->datestr_end, sizeof(char), datestr_len, vfd_file);
   if (read_elem != (size_t)datestr_len) {
      fprintf(stderr, "Error in reading vfd-header end date\n"
                      "Expected %d char, read %ld\n",
                      datestr_len, read_elem);
      exit(EXIT_FAILURE);
   }

   read_elem = fread(&(header->interval), sizeof(long long), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header interva\n"
                      "Expected 1 long long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   read_elem = fread(&(header->nprocesses), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header nprocesses\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   read_elem = fread(&(header->processID), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header processID\n"
                      "Expected 1 int, read %ld\n",
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
   read_elem = fread(&(header->nstacks), sizeof(unsigned int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header nstacks\n"
                      "Expected 1 unsigned int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(header->samples_offset), sizeof(long int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header samples_offset\n"
                      "Expected 1 long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(header->stacks_offset), sizeof(long int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header stacks_offset\n"
                      "Expected 1 long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(header->threadtree_offset), sizeof(long int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-header threadtree_offset\n"
                      "Expected 1 long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
}

void free_vfd_header(vfd_header_t *vfd_header) {
   vfd_header->vfd_version = 0;
   free(vfd_header->package_string);
   free(vfd_header->datestr_start);
   free(vfd_header->datestr_end);
   vfd_header->interval = 0ll;
   vfd_header->nprocesses = 0;
   vfd_header->processID = 0;
   vfd_header->nthreads = 0;
   vfd_header->runtime = 0.0;
   vfd_header->function_samplecount = 0;
   vfd_header->message_samplecount = 0;
   vfd_header->samples_offset = 0x0;
   vfd_header->stacks_offset = 0x0;
   vfd_header->threadtree_offset = 0x0;
   vfd_header->msgregsendcount = 0;
   vfd_header->msgregrecvcount = 0;
   free(vfd_header);
}

void print_vfd_header(vfd_header_t *vfd_header) {

   fprintf(stderr, "VFD-Header:\n");
   fprintf(stderr, "   vfd version:       %d\n", vfd_header->vfd_version);
   fprintf(stderr, "   vftrace version:   %s\n", vfd_header->package_string);
   fprintf(stderr, "   Start date:        %s\n", vfd_header->datestr_start);
   fprintf(stderr, "   End date:          %s\n", vfd_header->datestr_end);
   fprintf(stderr, "   MPI rank           %d (of %d)\n", vfd_header->processID,
                                                         vfd_header->nprocesses);
   fprintf(stderr, "   OMP threads:       %d\n", vfd_header->nthreads);
   fprintf(stderr, "   Sample interval:   %.6le seconds\n", vfd_header->interval*1.0e-9);
   fprintf(stderr, "   Runtime:           %.3lf seconds\n", vfd_header->runtime);
   fprintf(stderr, "   Samples:           %d\n", vfd_header->function_samplecount +
                                                 vfd_header->message_samplecount);
   fprintf(stderr, "      Function:       %d\n", vfd_header->function_samplecount);
   fprintf(stderr, "      Messages:       %d\n", vfd_header->message_samplecount);
   fprintf(stderr, "   Stacks:            %u\n", vfd_header->nstacks);
   fprintf(stderr, "   Stacks offset:     0x%lx\n", vfd_header->stacks_offset);
   fprintf(stderr, "   Sample offset:     0x%lx\n", vfd_header->samples_offset);
   fprintf(stderr, "   Threadtree offset: 0x%lx\n", vfd_header->threadtree_offset);
   fprintf(stderr, "\n");
}
