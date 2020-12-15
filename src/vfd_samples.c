#include <stdlib.h>
#include <stdio.h>

#include "vfd_types.h"
#include "mpi_types.h"
#include "vfd_samples.h"

void read_vfd_samples(FILE *vfd_file, vfd_header_t *header,
                      vfd_stack_sample_t **stack_samples_ptr,
                      vfd_message_sample_t **message_samples_ptr) {

   vfd_stack_sample_t *stack_samples = (vfd_stack_sample_t*)
      malloc(header->function_samplecount*sizeof(vfd_stack_sample_t));
   *stack_samples_ptr = stack_samples;

   vfd_message_sample_t *message_samples = (vfd_message_sample_t*)
      malloc(header->message_samplecount*sizeof(vfd_message_sample_t));
   *message_samples_ptr = message_samples;

   unsigned int tot_samplecount;
   tot_samplecount = header->function_samplecount + header->message_samplecount;
   unsigned int read_function_samplecount = 0;
   unsigned int read_message_samplecount = 0;

   fseek(vfd_file, header->sampleoffset, SEEK_SET);
   for (unsigned int isample=0; isample<tot_samplecount; isample++) {
      vfd_sample_kind_enum sample_kind;
      size_t read_elem;
      read_elem = fread(&sample_kind, sizeof(vfd_sample_kind_enum), 1, vfd_file);
      if (read_elem != 1) {
         fprintf(stderr, "Error in reading sample-kind\n"
                         "Expected 1 enum, read %ld\n",
                         read_elem);
         exit(EXIT_FAILURE);
      }

      vfd_stack_sample_t *fsample_ptr;
      vfd_message_sample_t *msample_ptr;

      switch (sample_kind) {
         case fnct_entry:
            // No break here so entry and exit execute the same code
         case fnct_exit:
            fsample_ptr = stack_samples + read_function_samplecount;
            *fsample_ptr = read_vfd_stack_sample(vfd_file);
            fsample_ptr->kind = sample_kind;
            read_function_samplecount++;
            break;
         case mpi_message:
            msample_ptr = message_samples + read_message_samplecount;
            *msample_ptr = read_vfd_message_sample(vfd_file);
            read_message_samplecount++;
            break;
         default:
            fprintf(stderr, "Unknown sample kind while reading vfd samples\n");
            exit(EXIT_FAILURE);
            break;
      }
   }

   if (read_function_samplecount != header->function_samplecount) {
      fprintf(stderr, "Expected %u function stack samples but read %u\n",
              header->function_samplecount, read_function_samplecount);
      exit(EXIT_FAILURE);
   }
   if (read_message_samplecount != header->message_samplecount) {
      fprintf(stderr, "Expected %u message samples but read %u\n",
              header->message_samplecount, read_message_samplecount);
      exit(EXIT_FAILURE);
   }
}

vfd_stack_sample_t read_vfd_stack_sample(FILE *vfd_file) {
   vfd_stack_sample_t stack_sample;
   size_t read_elem;
   read_elem = fread(&(stack_sample.stackID), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-stack sample id\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(stack_sample.sampletime), sizeof(long long), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-stack sample time\n"
                      "Expected 1 long long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   return stack_sample;
}

vfd_message_sample_t read_vfd_message_sample(FILE *vfd_file) {
   vfd_message_sample_t message_sample;
   size_t read_elem;
   read_elem = fread(&(message_sample.dir), sizeof(vfd_message_dir_enum), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message sample direction\n"
                      "Expected 1 enum, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message_sample.rank), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message sample rank\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message_sample.typeID), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message sample typeID\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message_sample.count), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message sample count\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message_sample.typeSize), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message sample typeSize\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message_sample.tag), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message sample tag\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message_sample.tstart_usec), sizeof(long long), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message sample tstart_usec\n"
                      "Expected 1 long long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   message_sample.dtstart_sec = message_sample.tstart_usec * 1.0e-6; // from microseconds to seconds
   read_elem = fread(&(message_sample.tend_usec), sizeof(long long), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message sample tend_usec\n"
                      "Expected 1 long long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   message_sample.dtend_sec = message_sample.tend_usec * 1.0e-6; // from microseconds to seconds
   message_sample.rate_MiBs = message_sample.count * message_sample.typeSize /
                       (message_sample.dtend_sec - message_sample.dtstart_sec) /
                       (1024.0 * 1024.0);
   read_elem = fread(&(message_sample.callingStackID), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message sample callingStackID\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   return message_sample;
}

void free_vfd_stack_samples(unsigned int nstack_samples,
                            vfd_stack_sample_t *stack_samples) {
   (void) nstack_samples;
   free(stack_samples);
}

void free_vfd_message_samples(unsigned int nmessage_samples,
                              vfd_message_sample_t *message_samples) {
   (void) nmessage_samples;
   free(message_samples);
}

void print_vfd_stack_samples(vfd_header_t *header, vfd_stack_sample_t *samples) {
   fprintf(stderr, "VFD stack samples:\n");
   unsigned int samplecount = header->function_samplecount;
   for (unsigned int isample=0; isample<samplecount; isample++) {
      fprintf(stderr, "%16.6lf", samples[isample].sampletime*1.0e-6);
      fprintf(stderr, " %s", samples[isample].kind == fnct_entry ? "call" : "exit");
      fprintf(stderr, " stackID=%d\n", samples[isample].stackID);
   }
}

void print_vfd_message_sampless(vfd_header_t *header,
                                vfd_message_sample_t *message_samples) {
   fprintf(stderr, "VFD message samples:\n");
   unsigned int msgcount = header->message_samplecount;
   for (unsigned int imsg=0; imsg<msgcount; imsg++) {
      fprintf(stderr, "%16.6f", message_samples[imsg].dtstart_sec);
      fprintf(stderr, " %s", message_samples[imsg].dir ? "recv" : "send");
      fprintf(stderr, " in stackID %d\n", message_samples[imsg].callingStackID);

      fprintf(stderr, "%16s", "");
      fprintf(stderr, " count=%d", message_samples[imsg].count);
      fprintf(stderr, " type=%s(%iBytes)",
                      get_mpitype_string_from_idx(message_samples[imsg].typeID),
                      message_samples[imsg].typeSize);
      fprintf(stderr, " rate=%8.4lf MiB/s", message_samples[imsg].rate_MiBs);
      fprintf(stderr, " peer=%d", message_samples[imsg].rank);
      fprintf(stderr, " tag=%d\n", message_samples[imsg].tag);

      fprintf(stderr, "%16.6lf", message_samples[imsg].dtend_sec);
      fprintf(stderr, " %s end\n", message_samples[imsg].dir ? "recv" : "send");
   }
}
