#ifndef VFD_STACKS_H
#define VFD_STACKS_H

#include <stdio.h>

#include "vfd_types.h"

void read_vfd_stacks(FILE *vfd_file, vfd_header_t *header,
                     vfd_stack_entry_t **stacks_ptr, int *maxlevel);

// returns a pointer to a vfd trace stack entry
// based on a list of callee indices
vfd_stack_entry_t *indexed_vfd_stack(int nidx, int*idx, vfd_t *vfdtrace);

void free_vfd_stacks(unsigned int nstacks, vfd_stack_entry_t *stacks);

void print_vfd_stacks(vfd_header_t *header, vfd_stack_entry_t *stacks);

#endif
