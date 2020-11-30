#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "vfd_types.h"
#include "vfd_header.h"

int main(int argc, char **argv) {

   // construct artificial vfd trace
   vfd_t *vfd = (vfd_t*) malloc(sizeof(vfd_t));;
   vfd->filepath = "nonexistent.vfd";
   vfd->filename = vfd->filepath;
   vfd->header = (vfd_header_t*) malloc(sizeof(vfd_header_t));

   // fill header
   vfd->header->vfd_version = 2;
   strcpy(vfd->header->vftrace_version, "VFTRACE 0010200");
   strcpy(vfd->header->date, "Wed Nov 25 10:43:37 2020");
   vfd->header->interval = 5000;
   vfd->header->nthreads = 1;
   vfd->header->mythread = 0;
   vfd->header->nranks = 1;
   vfd->header->myrank = 0;
   vfd->header->runtime = 7;
   vfd->header->function_samplecount = 2;
   vfd->header->message_samplecount = 0;
   vfd->header->fcallscount = 0;
   vfd->header->stackscount = 6;
   vfd->header->stacksoffset = 0;
   vfd->header->sampleoffset = 0;
   vfd->header->nhwc = 0;

   // show header
   print_vfd_header(vfd->header);

   // fill stacks list
   int nstacks = vfd->header->stackscount;
   vfd->maxlevel = 3;
   vfd->stacks = (vfd_stack_entry_t*) malloc(
      nstacks*sizeof(vfd_stack_entry_t));
   vfd->stacks[0].ID = 0;
   vfd->stacks[0].level = 0;
   vfd->stacks[0].callerID = 0;
   vfd->stacks[0].caller = NULL;
   vfd->stacks[0].ncallees = 0;
   vfd->stacks[0].callees = NULL;
   vfd->stacks[0].name = strdup("init");

   vfd->stacks[1].ID = 1;
   vfd->stacks[1].level = 1;
   vfd->stacks[1].callerID = 0;
   vfd->stacks[1].caller = NULL;
   vfd->stacks[1].ncallees = 0;
   vfd->stacks[1].callees = NULL;
   vfd->stacks[1].name = strdup("main");

   vfd->stacks[2].ID = 2;
   vfd->stacks[2].level = 2;
   vfd->stacks[2].callerID = 1;
   vfd->stacks[2].caller = NULL;
   vfd->stacks[2].ncallees = 0;
   vfd->stacks[2].callees = NULL;
   vfd->stacks[2].precise = false;
   vfd->stacks[2].name = strdup("f1");

   vfd->stacks[3].ID = 3;
   vfd->stacks[3].level = 3;
   vfd->stacks[3].callerID = 2;
   vfd->stacks[3].caller = NULL;
   vfd->stacks[3].ncallees = 0;
   vfd->stacks[3].callees = NULL;
   vfd->stacks[3].precise = false;
   vfd->stacks[3].name = strdup("f2");

   vfd->stacks[4].ID = 4;
   vfd->stacks[4].level = 2;
   vfd->stacks[4].callerID = 1;
   vfd->stacks[4].caller = NULL;
   vfd->stacks[4].ncallees = 0;
   vfd->stacks[4].callees = NULL;
   vfd->stacks[4].precise = false;
   vfd->stacks[4].name = strdup("f3");

   vfd->stacks[5].ID = 5;
   vfd->stacks[5].level = 3;
   vfd->stacks[5].callerID = 4;
   vfd->stacks[5].caller = NULL;
   vfd->stacks[5].ncallees = 0;
   vfd->stacks[5].callees = NULL;
   vfd->stacks[5].precise = false;
   vfd->stacks[5].name = strdup("f4");

   // fill in automatically constructable information
   for (unsigned int istack=0; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = vfd->stacks+istack;
      stack_ptr->precise = false;
      stack_ptr->visible_in_treeview = true;
      stack_ptr->namelen = strlen(stack_ptr->name);
      stack_ptr->caller = vfd->stacks+stack_ptr->callerID;
      (vfd->stacks[stack_ptr->callerID].ncallees)++;
   }
   // allocate memory to hold the callee pointers
   for (unsigned int istack=0; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = vfd->stacks+istack;
      stack_ptr->callees = (vfd_stack_entry_t**)
         malloc(stack_ptr->ncallees * sizeof(vfd_stack_entry_t*));
      for (int icallee=0; icallee < stack_ptr->ncallees; icallee++) {
         stack_ptr->callees[icallee] = NULL;
      }
   }
   // go through all stacks and register the callees
   for (unsigned int istack=0; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = vfd->stacks+istack;
      vfd_stack_entry_t *caller = stack_ptr->caller;
      bool registered = false;
      for (int icallee=0; icallee < caller->ncallees; icallee++) {
         if (caller->callees[icallee] == NULL) {
            registered = true;
            caller->callees[icallee] = stack_ptr;
            break;
         }
      }
      if (!registered) {
         fprintf(stderr, "Not enough memory allocated to register callee\n");
         exit(EXIT_FAILURE);
      }
   }

   // show stacks
   print_vfd_stacks(vfd->header, vfd->stacks);

   // fill stack samples
   vfd->stack_samples = (vfd_stack_sample_t*)
       malloc(vfd->header->function_samplecount*sizeof(vfd_stack_sample_t));
   vfd_message_t *messages = (vfd_message_t*)
      malloc(vfd->header->message_samplecount*sizeof(vfd_message_t));

   vfd->stack_samples[0].kind = fnct_entry;
   vfd->stack_samples[0].stackID = 0;
   vfd->stack_samples[0].sampletime = 0ll;

   vfd->stack_samples[1].kind = fnct_exit;
   vfd->stack_samples[1].stackID = 0;
   vfd->stack_samples[1].sampletime = 11000000ll;

   // show samples
   print_vfd_stack_samples(vfd->header, vfd->stack_samples);

   // construct fcalls from stack samples
   construct_vfd_fcalls(vfd);

   // show constructed fcalls
   print_vfd_fcalls(vfd->header, vfd->fcalls);

}
