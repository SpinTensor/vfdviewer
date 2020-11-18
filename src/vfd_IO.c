#include <stdio.h>

#include "vfd_types.h"
#include "vfd_IO.h"

vfd_t read_vfd_file(FILE *vfd_file) {
   vfd_t vfd;
   vfd.header = read_vfd_header(vfd_file);
#ifdef _DEBUG
   print_vfd_header(vfd.header);
#endif
   return vfd;
}

vfd_header_t read_vfd_header(FILE *vfd_file) {
   vfd_header_t header;

   fread(&(header.vfd_version), 1, sizeof(int), vfd_file);
   fread(&(header.vftrace_version), 1, VFTR_VERSIONSIZE*sizeof(char), vfd_file);
   header.vftrace_version[VFTR_VERSIONSIZE] = '\0';
   fread(&(header.date), 1, DATESTRINGSIZE*sizeof(char), vfd_file);
   header.date[DATESTRINGSIZE] = '\0';
   fread(&(header.interval), 1, sizeof(long long), vfd_file);
   fread(&(header.nthreads), 1, sizeof(int), vfd_file);
   fread(&(header.mythread), 1, sizeof(int), vfd_file);
   fread(&(header.nranks), 1, sizeof(int), vfd_file);
   fread(&(header.myrank), 1, sizeof(int), vfd_file);
   fread(&(header.runtime), 1, sizeof(double), vfd_file);
   fread(&(header.function_samplecount), 1, sizeof(unsigned int), vfd_file);
   fread(&(header.message_samplecount), 1, sizeof(unsigned int), vfd_file);
   fread(&(header.stackscount), 1, sizeof(unsigned int), vfd_file);
   fread(&(header.stacksoffset), 1, sizeof(long), vfd_file);
   fread(&(header.sampleoffset), 1, sizeof(long), vfd_file);

   return header;
}

//vfd_stack_entry_t *read_vfd_stacks(FILE *vfd_file, vfd_header_t);
//
//vfd_stack_sample_t read_vfd_stack_sample(FILE *vfd_file);
//
//vfd_message_t read_vfd_message_sample(FILE *vfd_file);

void print_vfd_header(vfd_header_t vfd_header) {
   fprintf(stderr, "vfd version:     %d\n", vfd_header.vfd_version);
   fprintf(stderr, "vftrace version: %s\n", vfd_header.vftrace_version);
   fprintf(stderr, "Date:            %s\n", vfd_header.date);
   fprintf(stderr, "MPI rank         %d (of %d)\n", vfd_header.myrank,
                                                    vfd_header.nranks);
   fprintf(stderr, "OMP thread       %d (of %d)\n", vfd_header.mythread,
                                                    vfd_header.nthreads);
   fprintf(stderr, "Sample interval: %.6le seconds\n", vfd_header.interval*1.0e-6);
   fprintf(stderr, "Runtime:         %.3lf seconds\n", vfd_header.runtime);
   fprintf(stderr, "Samples:         %d\n", vfd_header.function_samplecount + 
                                            vfd_header.message_samplecount);
   fprintf(stderr, "   Function:     %d\n", vfd_header.function_samplecount);
   fprintf(stderr, "   Messages:     %d\n", vfd_header.message_samplecount);
   fprintf(stderr, "Stacks:          %u\n", vfd_header.stackscount);
   fprintf(stderr, "Stacks offset:   0x%lx\n", vfd_header.stacksoffset);
   fprintf(stderr, "Sample offset:   0x%lx\n", vfd_header.sampleoffset);
}


