#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vfd_types.h"
#include "vfd_header.h"
#include "vfd_stacks.h"
#include "vfd_samples.h"
#include "vfd_fcalls.h"
#include "vfd_msgreg.h"
#include "vfd_sort.h"

#include "vgtk_handles.h"

static vfd_t *g_vfd_list = NULL;

// create a new vfd trace from a file
vfd_t *new_vfd(char *vfdpath) {

   // allocate memory to hold the vfd data structure
   vfd_t *new_vfd = (vfd_t*) malloc(sizeof(vfd_t));

   // open the file to read the vfdfile
   new_vfd->filepath = vfdpath;
   FILE *vfd_handle = fopen(new_vfd->filepath, "r");

   // read the header information
   read_vfd_header(vfd_handle, &(new_vfd->header));
   // read the stack information
   read_vfd_stacks(vfd_handle, new_vfd->header,
                   &(new_vfd->stacks), &(new_vfd->maxlevel));
   // read stack and message samples
   // they are wildly mixed so there is no chance
   // of reading them separately in one go
   read_vfd_samples(vfd_handle, new_vfd->header,
                    &(new_vfd->stack_samples),
                    &(new_vfd->message_samples));
   fclose(vfd_handle);

   // sort the message samples
   shellsort_message_samples(new_vfd->header->message_samplecount,
                             new_vfd->message_samples);

   // construct message regions
   construct_vfd_msgregs(new_vfd);

   // construct the function calls timeline
   construct_vfd_fcalls(new_vfd);

   // sort the fcalls
   shellsort_fcalls(new_vfd->header->fcallscount,
                    new_vfd->fcalls);

   // find the last occurence of '/',
   // which marks the end of the filepath
   new_vfd->filename = strrchr(new_vfd->filepath, '/');
   // if the filename has no path only the filename
   // simply point to the path pointer
   if (new_vfd->filename == NULL) {
      new_vfd->filename = new_vfd->filepath;
   } else {
      // move pointer one over to
      // not start on '/' but after it
      new_vfd->filename++;
   }

   // create the storage space for gtk handles for the vfd-trace
   new_vfd->vgtk_handles = new_vgtk_handles();

   // initialize the linked list connectors
   new_vfd->next = NULL;
   new_vfd->prev = NULL;

#ifdef _DEBUG
   print_vfd_header(new_vfd->header);
   print_vfd_stacks(new_vfd->header, new_vfd->stacks);
   print_vfd_stack_samples(new_vfd->header, new_vfd->stack_samples);
   print_vfd_message_samples(new_vfd->header, new_vfd->message_samples);
   print_vfd_msgregs(new_vfd->header,
                     new_vfd->msgregs_send,
                     new_vfd->msgregs_recv);
   print_vfd_fcalls(new_vfd->header, new_vfd->fcalls);
#endif

   return new_vfd;
}

// free a vfd trace
void free_vfd(vfd_t **vfd_ptr) {
   vfd_t *vfd = *vfd_ptr;

   // free the struct members
   // done in reverse order, because some
   // free routines might need header information
   free_vfd_stacks(vfd->header->stackscount, vfd->stacks);
   vfd->stacks = NULL;

   free_vfd_message_samples(vfd->header->message_samplecount, vfd->message_samples);
   vfd->message_samples = NULL;

   free_vfd_msgregs(vfd->header->msgregsendcount, vfd->msgregs_send);
   vfd->msgregs_send = NULL;
   free_vfd_msgregs(vfd->header->msgregrecvcount, vfd->msgregs_recv);
   vfd->msgregs_recv = NULL;

   free_vfd_stack_samples(vfd->header->function_samplecount, vfd->stack_samples);
   vfd->stack_samples = NULL;

   free_vfd_fcalls(vfd->header->function_samplecount, vfd->fcalls);
   vfd->fcalls = NULL;

   free_vfd_header(vfd->header);
   vfd->header = NULL;

   free(vfd->filepath);
   vfd->filepath = NULL;

   free_vgtk_handles(&(vfd->vgtk_handles));

   // free the vfd struct pointer itself
   vfd = NULL;
   free(*vfd_ptr);
   *vfd_ptr = NULL;
}

// prepend vfd trace to the vfd list
void prepend_vfd(vfd_t *new_vfd) {
   if (g_vfd_list == NULL) {
      // list is empty
      // this is the first element
      g_vfd_list = new_vfd;
      g_vfd_list->prev = NULL;
      g_vfd_list->next = NULL;
   } else {
      // list contains entries
      new_vfd->next = g_vfd_list;
      new_vfd->prev = NULL;
      g_vfd_list->prev = new_vfd;
      g_vfd_list = new_vfd;
   }
}

// append vfd trace to the vfd list
void append_vfd(vfd_t *new_vfd) {
   if (g_vfd_list == NULL) {
      // list is empty
      // this is the first element
      new_vfd->prev = NULL;
      new_vfd->next = NULL;
      g_vfd_list = new_vfd;
   } else {
      vfd_t *tmp_vfd_ptr = g_vfd_list;
      // there are already elements in the list
      // go to the end
      while (tmp_vfd_ptr->next != NULL) {
         tmp_vfd_ptr = tmp_vfd_ptr->next;
      }
      // connect the last element with the new one
      tmp_vfd_ptr->next = new_vfd;
      // connect the new with the (former) last one
      new_vfd->prev = tmp_vfd_ptr;
      // nullify the next pointer of the new entry
      // to indicate termination of the list
      new_vfd->next = NULL;
   }
}

// remove vfd trace from the vfd trace list
void remove_vfd(vfd_t *vfd) {
   if (vfd->prev == NULL) {
      // is the first element in the list
      if (vfd->next == NULL) {
         // only entry in the list
         g_vfd_list = NULL;
      } else {
         // first element in the list
         g_vfd_list = vfd->next;
         vfd->next->prev = NULL;
      }
   } else {
      if (vfd->next == NULL) {
         // last element in the list
         vfd->prev->next = NULL;
      } else {
         // somewhere in the middle of the list
         vfd->prev->next = vfd->next;
         vfd->next->prev = vfd->prev;
      }
   }
}

// number of vfd traces in the list
int num_vfds() {
   int n = 0;
   vfd_t *tmp_vfd_ptr = g_vfd_list;
   while (tmp_vfd_ptr != 0) {
      n++;
      tmp_vfd_ptr = tmp_vfd_ptr->next;
   }
   return n;
}

// returns a pointer to the first vfd trace entry
// returns NULL if the list is empty
vfd_t *first_vfd() {
   return g_vfd_list;
}

// returns a pointer to the last vfd trace entry
// returns NULL if the list is empty
vfd_t *last_vfd() {
   if (g_vfd_list == NULL) {
      return NULL;
   } else {
      vfd_t *tmp_vfd_ptr = g_vfd_list;
      while (tmp_vfd_ptr->next != NULL) {
         tmp_vfd_ptr = tmp_vfd_ptr->next;
      }
      return tmp_vfd_ptr;
   }
}

// returns a pointer to the n-th vfd trace entry
// NULL if the list is shorter than n
// negative indices count from the back of the list
// e.g. [a,b,c,d,e]
// nth_vfd(0) = a
// nth_vfd(2) = c
// nth_vfd(-1) = e
// nth_vfd(-3) = c
vfd_t *nth_vfd(int n) {
   if (g_vfd_list == NULL) {
      return NULL;
   }
   if (n < 0) {
      // start from the back of the list
      n++;
      vfd_t *tmp_vfd_ptr = last_vfd();
      while (n < 0 && tmp_vfd_ptr->prev != NULL) {
         tmp_vfd_ptr = tmp_vfd_ptr->prev;
         n++;
      }
      if (n != 0) {
         return NULL;
      } else {
         return tmp_vfd_ptr;
      }
   } else {
      // start from the beginning of the list
      vfd_t *tmp_vfd_ptr = g_vfd_list;
      while (n > 0 && tmp_vfd_ptr->next != NULL) {
         tmp_vfd_ptr = tmp_vfd_ptr->next;
         n--;
      }
      if (n != 0) {
         return NULL;
      } else {
         return tmp_vfd_ptr;
      }
   }
}

// returns a pointer to a vfd trace stack entry
// based on a list of callee indices
void indexed_vfd_trace_and_stack(int nidx, int *idx,
                                 vfd_t **vfdtrace,
                                 vfd_stack_entry_t **vfd_stack) {

   if (nidx == 0) {
      *vfdtrace = NULL;
      *vfd_stack = NULL;
   } else {
      // first index corresponds to the vfd trace position in the list
      *vfdtrace = nth_vfd(idx[0]);
      // get the stack entry for that vfd trace
      // ommit the first index as it is not used for the stacks
      *vfd_stack = indexed_vfd_stack(nidx-1, idx+1, *vfdtrace);
   }
}

// returns a pointer to a list of callee indices
// based on a vfd trace and the stack
void indexlist_from_vfd_trace_and_stack(vfd_t *vfdtrace,
                                        vfd_stack_entry_t *vfd_stack,
                                        int *nidx_ptr, int **idx_ptr) {

   if (vfd_stack->level == 0) {
      *nidx_ptr = 0;
      *idx_ptr = NULL;
   }

   // get the level of the stack entry
   // and create the callee indices list
   int nidx = vfd_stack->level+1;
   *nidx_ptr = nidx;
   int *idx = (int*) malloc(nidx*sizeof(int));
   *idx_ptr = idx;
   for (int iidx=0; iidx<nidx; iidx++) {
      idx[iidx] = -1;
   }

   // fill the list from the back
   for (int iidx=nidx-1; iidx>0; iidx--) {
      vfd_stack_entry_t *caller_stack = vfd_stack->caller;
      // go through all callees of the caller stack and compare the IDs
      for (int icallee=0; icallee<caller_stack->ncallees; icallee++) {
         if (caller_stack->callees[icallee]->ID == vfd_stack->ID) {
            idx[iidx] = icallee;
            vfd_stack = caller_stack;
            break;
         }
      }
   }

   // second index is special as it is one less than determined
   // as the self referential init stack is skipped.
   idx[1]--;

   // first index corresponds to the vfd trace position in the list
   vfd_t *tmpvfd = first_vfd();
   int ivfd = 0;
   while (tmpvfd != NULL) {
      if (vfdtrace == tmpvfd) {
         tmpvfd = NULL;
      } else {
         tmpvfd = tmpvfd->next;
         ivfd++;
      }
   }
   idx[0] = ivfd;
}

// returns the maximum of all maxlevel
int vfds_max_maxlevel() {
   int mmlvl = -1;
   vfd_t *vfd = first_vfd();
   while (vfd != NULL) {
      mmlvl = vfd->maxlevel > mmlvl ? vfd->maxlevel : mmlvl;
      vfd = vfd->next;
   }

   return mmlvl;
}

// returns the maximum of all runtimes
double vfds_max_runtime() {
   double maxrt = 0.0;
   vfd_t *vfd = first_vfd();
   while (vfd != NULL) {
      maxrt = vfd->header->runtime > maxrt ? vfd->header->runtime : maxrt;
      vfd = vfd->next;
   }

   return maxrt;
}

// remove every element in the vfd trace list
// and free them
void remove_and_free_vfd_list() {
   vfd_t *tmpvfd = first_vfd();
   while (tmpvfd != NULL) {
      remove_vfd(tmpvfd);
      free_vfd(&tmpvfd);
      tmpvfd = first_vfd();
   }
}
