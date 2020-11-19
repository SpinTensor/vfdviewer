#ifndef VFD_IO_H
#define VFD_IO_H

#include <stdio.h>

#include "vfd_types.h"

vfd_stack_entry_t *read_vfd_stacks(FILE *vfd_file, vfd_header_t);

vfd_stack_sample_t read_vfd_stack_sample(FILE *vfd_file);

vfd_message_t read_vfd_message_sample(FILE *vfd_file);

void read_vfd_file(vfd_t *vfd_file);

#endif
