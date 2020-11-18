#ifndef VFD_STACKS_IO_H
#define VFD_STACKS_IO_H

#include <stdio.h>

#include "vfd_types.h"

vfd_stack_entry_t *read_vfd_stacks(FILE *vfd_file, vfd_header_t header);

void print_vfd_stacks(vfd_stack_entry_t *stacks, vfd_header_t header);

#endif
