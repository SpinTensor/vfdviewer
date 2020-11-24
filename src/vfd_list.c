#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vfd_types.h"
#include "vfd_header.h"
#include "vfd_stacks.h"
#include "vfd_samples.h"

static vfd_t *g_vfd_list = NULL;

// create a new vfd trace from a file
vfd_t *new_vfd(char *filename) {

   // allocate memory to hold the vfd data structure
   vfd_t *new_vfd = (vfd_t*) malloc(sizeof(vfd_t));

   // open the file to read the vfdfile
   new_vfd->filename = filename;
   FILE *vfd_handle = fopen(filename, "r");

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
                    &(new_vfd->messages));
   fclose(vfd_handle);

   new_vfd->next = NULL;
   new_vfd->prev = NULL;

#ifdef _DEBUG
   print_vfd_header(new_vfd->header);
   print_vfd_stacks(new_vfd->header, new_vfd->stacks);
   print_vfd_stack_samples(new_vfd->header, new_vfd->stack_samples);
   print_vfd_messages(new_vfd->header, new_vfd->messages);
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

   free_vfd_messages(vfd->header->message_samplecount, vfd->messages);
   vfd->messages = NULL;

   free_vfd_stack_samples(vfd->header->function_samplecount, vfd->stack_samples);
   vfd->stack_samples = NULL;

   free_vfd_header(vfd->header);
   vfd->header = NULL;

   free(vfd->filename);
   vfd->filename = NULL;

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
void indexed_vfd_trace_and_stack(int nidx, int*idx,
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
