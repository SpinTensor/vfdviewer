#ifndef VFD_STACKS_H
#define VFD_STACKS_H

#include <stdio.h>
#include <regex.h>

#include "vfd_types.h"

void read_vfd_stacks(FILE *vfd_file, vfd_header_t *header,
                     vfd_stack_entry_t **stacks_ptr, int *maxlevel);

// returns a pointer to a vfd trace stack entry
// based on a list of callee indices
vfd_stack_entry_t *indexed_vfd_stack(int nidx, int*idx, vfd_t *vfdtrace);

// precompute the visibility of each stack
// so that the actual visibility function
// can simply lookup the value, instead
// of computing it in exponential time.
bool update_stack_visible_in_treeview(regex_t *regex,
                                      vfd_stack_entry_t *stack);

// precompute the visibility of each stack
// so that the actual visibility function
// can simply lookup the value, instead
// of computing it in exponential time.
bool update_stack_visible_in_listview(regex_t *regex,
                                      vfd_stack_entry_t *stack);

void free_vfd_stacks(unsigned int nstacks, vfd_stack_entry_t *stacks);

int get_stack_string_length(vfd_stack_entry_t *stack);

char *get_stack_string(vfd_stack_entry_t *stack);

void print_vfd_stacks(vfd_header_t *header, vfd_stack_entry_t *stacks);

#endif
