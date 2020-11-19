#include <stdlib.h>
#include <stdio.h>

#include "vfd_types.h"
#include "mpi_types.h"
#include "vfd_samples.h"

void read_vfd_samples(FILE *vfd_file, vfd_header_t *header,
                      vfd_stack_sample_t **stack_samples_ptr,
                      vfd_message_t **messages_ptr) {

   vfd_stack_sample_t *stack_samples = (vfd_stack_sample_t*)
      malloc(header->function_samplecount*sizeof(vfd_stack_sample_t));
   *stack_samples_ptr = stack_samples;

   vfd_message_t *messages = (vfd_message_t*)
      malloc(header->message_samplecount*sizeof(vfd_message_t));
   *messages_ptr = messages;

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
      vfd_message_t *msample_ptr;

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
            msample_ptr = messages + read_message_samplecount;
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
      fprintf(stderr, "Expected %u messages but read %u\n",
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

vfd_message_t read_vfd_message_sample(FILE *vfd_file) {
   vfd_message_t message;
   size_t read_elem;
   read_elem = fread(&(message.dir), sizeof(vfd_message_dir_enum), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message direction\n"
                      "Expected 1 enum, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message.rank), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message rank\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message.typeID), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message typeID\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message.count), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message count\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message.typeSize), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message typeSize\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message.tag), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message tag\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   read_elem = fread(&(message.tstart_usec), sizeof(long long), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message tstart_usec\n"
                      "Expected 1 long long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   message.dtstart_sec = message.tstart_usec * 1.0e-6; // from microseconds to seconds
   read_elem = fread(&(message.tend_usec), sizeof(long long), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message tend_usec\n"
                      "Expected 1 long long, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }
   message.dtend_sec = message.tend_usec * 1.0e-6; // from microseconds to seconds
   message.rate_MiBs = message.count * message.typeSize /
                       (message.dtend_sec - message.dtstart_sec) / 
                       (1024.0 * 1024.0);
   read_elem = fread(&(message.callingStackID), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading vfd-message callingStackID\n"
                      "Expected 1 int, read %ld\n",
                      read_elem);
      exit(EXIT_FAILURE);
   }

   return message;
}

void free_vfd_stack_samples(unsigned int nstack_samples,
                            vfd_stack_sample_t *stack_samples) {
   (void) nstack_samples;
   free(stack_samples);
}

void free_vfd_messages(unsigned int nmessages, vfd_message_t *messages) {
   (void) nmessages;
   free(messages);
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

void print_vfd_messages(vfd_header_t *header, vfd_message_t *messages) {
   fprintf(stderr, "VFD message samples:\n");
   unsigned int msgcount = header->message_samplecount;
   for (unsigned int imsg=0; imsg<msgcount; imsg++) {
      fprintf(stderr, "%16.6f", messages[imsg].dtstart_sec);
      fprintf(stderr, " %s", messages[imsg].dir ? "recv" : "send");
      fprintf(stderr, " in stackID %d\n", messages[imsg].callingStackID);

      fprintf(stderr, "%16s", "");
      fprintf(stderr, " count=%d", messages[imsg].count);
      fprintf(stderr, " type=%s(%iBytes)",
                      get_mpitype_string_from_idx(messages[imsg].typeID),
                      messages[imsg].typeSize);
      fprintf(stderr, " rate=%8.4lf MiB/s", messages[imsg].rate_MiBs);
      fprintf(stderr, " peer=%d", messages[imsg].rank);
      fprintf(stderr, " tag=%d\n", messages[imsg].tag);

      fprintf(stderr, "%16.6lf", messages[imsg].dtend_sec);
      fprintf(stderr, " %s end\n", messages[imsg].dir ? "recv" : "send");
   }
}
