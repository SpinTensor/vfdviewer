#include <stdio.h>
#include <stdlib.h>

#include "vfd_types.h"
#include "vfd_header_IO.h"
#include "vfd_stacks_IO.h"
#include "vfd_samples_IO.h"

vfd_t *g_vfd_list = NULL;

// add a new vfd trace to the list
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
                   &(new_vfd->stacks));
   // read stack and message samples 
   // they are wildly mixed so there is no chance
   // of reading them separately in one go
   read_vfd_samples(vfd_handle, new_vfd->header,
                    &(new_vfd->stack_samples),
                    &(new_vfd->messages));
   fclose(vfd_handle);

#ifdef _DEBUG
   print_vfd_header(new_vfd->header);
   print_vfd_stacks(new_vfd->header, new_vfd->stacks);
   print_vfd_stack_samples(new_vfd->header, new_vfd->stack_samples);
   print_vfd_messages(new_vfd->header, new_vfd->messages);
#endif

   return new_vfd;
}

//   vfd_t *tmp_vfd_ptr = vfd_trace_list;
//   if (tmp_vfd_ptr == NULL) {
//      // is first element in the list
//      tmp_vfd_ptr->prev = NULL;
//      tmp_vfd_ptr->next = NULL;
//      vfd_trace_list = tmp_vfd_ptr;
//   } else {
//      // there are already elements in the list
//      // go to the end
//      while (tmp_vfd_ptr->next != NULL) {
//      }
//      // connect the last element with the new one
//      tmp_vfd_ptr->next = new_vfd;
//      // connect the new with the (former) last one
//      new_vfd->prev = tmp_vfd_ptr;
//      // nullify the next pointer of the new entry
//      // to indicate termination of the list
//      new_vfd->next = NULL;
//   }
//
//   // return pointer to new vfd entry
//   return new_vfd;
//}
//
//void remove_vfd_from_list(vft_t *old_vfd) {
//   if (old_vfd->prev = NULL) {
//      // is the first element in the list
//      if (old_vfd->next = NULL) {
