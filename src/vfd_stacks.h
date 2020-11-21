#ifndef VFD_STACKS_H
#define VFD_STACKS_H

#include <stdio.h>

#include "vfd_types.h"

void read_vfd_stacks(FILE *vfd_file, vfd_header_t *header,
                     vfd_stack_entry_t **stacks_ptr, int *maxlevel);

void free_vfd_stacks(unsigned int nstacks, vfd_stack_entry_t *stacks);

void print_vfd_stacks(vfd_header_t *header, vfd_stack_entry_t *stacks);

#endif
