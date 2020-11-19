#ifndef VFD_SAMPLES_IO_H
#define VFD_SAMPLES_IO_H

#include <stdio.h>

#include "vfd_types.h"

void read_vfd_samples(FILE *vfd_file, vfd_header_t *header,
                      vfd_stack_sample_t **stack_samples_ptr,
                      vfd_message_t **messages_ptr);

vfd_stack_sample_t read_vfd_stack_sample(FILE *vfd_file);

vfd_message_t read_vfd_message_sample(FILE *vfd_file);

void print_vfd_stack_samples(vfd_header_t *header, vfd_stack_sample_t *samples);

void print_vfd_messages(vfd_header_t *header, vfd_message_t *messages);

#endif
