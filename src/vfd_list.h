#ifndef VFD_LIST_H
#define VFD_LIST_H

#include "vfd_types.h"

// create a new vfd trace from a file
vfd_t *new_vfd(char *filename);

// free a vfd trace
void free_vfd(vfd_t **vfd_ptr);

// prepend vfd trace to the vfd list
void prepend_vfd(vfd_t *new_vfd);

// append vfd trace to the vfd list
void append_vfd(vfd_t *new_vfd);

// remove vfd trace from the vfd trace list
void remove_vfd(vfd_t *vfd);

// number of vfd traces in the list
int num_vfds();

// returns a pointer to the first vfd trace entry
// returns NULL if the list is empty
vfd_t *first_vfd();

// returns a pointer to the last vfd trace entry
// returns NULL if the list is empty
vfd_t *last_vfd();

// returns a pointer to the n-th vfd trace entry
// NULL if the list is shorter than n
// negative indices count from the back of the list
// e.g. [a,b,c,d,e]
// nth_vfd(0) = a
// nth_vfd(2) = c
// nth_vfd(-1) = e
// nth_vfd(-3) = c
vfd_t *nth_vfd(int n);

// return the vfd trace position
// when given a vfd pointer
int vfd_position(vfd_t *vfd_ptr);

// returns a pointer to a vfd trace stack entry
// based on a list of callee indices
void indexed_vfd_trace_and_stack(int nidx, int*idx,
                                 vfd_t **vfdtrace,
                                 vfd_stack_entry_t **vfd_stack);

// returns a pointer to a list of callee indices
// based on a vfd trace and the stack
void indexlist_from_vfd_trace_and_stack(vfd_t *vfdtrace,
                                        vfd_stack_entry_t *vfd_stack,
                                        int *nidx_ptr, int **idx_ptr);

// returns the maximum of all maxlevel
int vfds_max_maxlevel();

// returns the maximum of all runtimes
double vfds_max_runtime();

// returns the number of processes for the loaded vfd-files
int vfds_nprocs();

// remove every element in the vfd trace list
// and free them
void remove_and_free_vfd_list();

#endif
