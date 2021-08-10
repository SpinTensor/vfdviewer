#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>

#include "vfd_types.h"
#include "vgtk_colors.h"
#include "hashing.h"

vfd_stack_entry_t *read_vfd_stacks(FILE *vfd_file, vfd_header_t *header,
                                   vfd_stack_entry_t **stacks_ptr, int *maxlevel) {
   unsigned int nstacks = header->stackscount;
   *maxlevel = 0;

   *stacks_ptr = (vfd_stack_entry_t*) malloc(nstacks*sizeof(vfd_stack_entry_t));
   vfd_stack_entry_t *stacks = *stacks_ptr;
   memset((void*) stacks, 0, nstacks*sizeof(vfd_stack_entry_t));

   // Read in the vfd information
   fseek(vfd_file, header->stacksoffset, SEEK_SET);
   for (unsigned int istack=0; istack<nstacks; istack++) {
      int id;
      size_t read_elem;
      read_elem = fread(&id, sizeof(int), 1, vfd_file);
      if (read_elem != 1) {
         fprintf(stderr, "Error in reading vfd-stack nr. %u: ID\n"
                         "Expected 1 int, read %ld\n",
                         istack, read_elem);
         exit(EXIT_FAILURE);
      }
      if ((unsigned int) id >= nstacks) {
         fprintf(stderr, "Error in stack ID: %d is larger than number of stacks %d\n",
                         id, nstacks);
         exit(EXIT_FAILURE);
      }
      vfd_stack_entry_t *stack_ptr = stacks+id;
      stack_ptr->ID = id;
      read_elem = fread(&(stack_ptr->level), sizeof(int), 1, vfd_file);
      if (read_elem != 1) {
         fprintf(stderr, "Error in reading vfd-stack nr. %u: level\n"
                         "Expected 1 int, read %ld\n",
                         istack, read_elem);
         exit(EXIT_FAILURE);
      }
      // reduce level by one as init starts with level one
      // but everything is easier if it starts at zero
      stack_ptr->level--;
      // update maximum level
      *maxlevel = stack_ptr->level > *maxlevel ? stack_ptr->level : *maxlevel;

      read_elem = fread(&(stack_ptr->callerID), sizeof(int), 1, vfd_file);
      if (read_elem != 1) {
         fprintf(stderr, "Error in reading vfd-stack nr. %u: callerID\n"
                         "Expected 1 int, read %ld\n",
                         istack, read_elem);
         exit(EXIT_FAILURE);
      }
      read_elem = fread(&(stack_ptr->namelen), sizeof(int), 1, vfd_file);
      if (read_elem != 1) {
         fprintf(stderr, "Error in reading vfd-stack nr. %u: namelen\n"
                         "Expected 1 int, read %ld\n",
                         istack, read_elem);
         exit(EXIT_FAILURE);
      }
      stack_ptr->name = (char*) malloc((stack_ptr->namelen+1)*sizeof(char));
      read_elem = fread(stack_ptr->name, sizeof(char), stack_ptr->namelen, vfd_file);
      if (read_elem != (size_t) (stack_ptr->namelen)) {
         fprintf(stderr, "Error in reading vfd-stack nr. %u: name\n"
                         "Expected 1 int, read %ld\n",
                         istack, read_elem);
         exit(EXIT_FAILURE);
      }
      stack_ptr->name[stack_ptr->namelen] = '\0';
   }


   // no additional data on the stacks is read in.
   // the rest is derived
   for (unsigned int istack=0; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = stacks+istack;
      // if the function is precise
      stack_ptr->precise = stack_ptr->name[stack_ptr->namelen-1] == '*';
      // remove the asterisk from the name
      if (stack_ptr->precise) {
         stack_ptr->name[stack_ptr->namelen-1] = '\0';
      }
      // if the function should be visible in the treeview
      stack_ptr->visible_in_treeview = true;
      // if the function should be visible in the listview
      stack_ptr->visible_in_listview = true;
      // who called this function?
      stack_ptr->caller = stacks+stack_ptr->callerID;
      // determine the default color for drawing this stack entry
      uint32_t namehash = jenkins_32_hash(stack_ptr->namelen,
                                          (uint8_t*) stack_ptr->name);
      stack_ptr->drawcolor = vgtk_color_list[namehash%vgtk_ncolors];

      // increament the callee counter for the calling function
      (stacks[stack_ptr->callerID].ncallees)++;
   }

   // allocate memory to hold the callee pointers
   for (unsigned int istack=0; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = stacks+istack;
      stack_ptr->callees = (vfd_stack_entry_t**)
         malloc(stack_ptr->ncallees * sizeof(vfd_stack_entry_t*));
      for (int icallee=0; icallee < stack_ptr->ncallees; icallee++) {
         stack_ptr->callees[icallee] = NULL;
      }
   }

   // go through all stacks and register the callees
   for (unsigned int istack=0; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = stacks+istack;
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

   return stacks;
}

// returns a pointer to a vfd trace stack entry
// based on a list of callee indices
vfd_stack_entry_t *indexed_vfd_stack(int nidx, int*idx, vfd_t *vfdtrace) {
   if (nidx == 0) {return NULL;}
   // first index is off by one.
   // init first points to itself as callee
   vfd_stack_entry_t *stacks = vfdtrace->stacks;
   vfd_stack_entry_t *entry;
   entry = stacks->callees[idx[0]+1];

   // follow the indexed path through the stack
   for (int iidx=1; iidx<nidx; iidx++){
      entry = entry->callees[idx[iidx]];
   }

   return entry;
}

// precompute the visibility of each stack
// so that the actual visibility function
// can simply lookup the value, instead
// of computing it in exponential time.
bool update_stack_visible_in_treeview(regex_t *regex,
                                      vfd_stack_entry_t *stack) {
   // a stack should only be visible if
   // 1. its function name matches the regular expression
   // OR
   // 2. one of its callees is visible
   stack->visible_in_treeview = false;

   // check if any of the callees is visible
   for (int icallee=0; icallee<stack->ncallees; icallee++) {
      bool child_visible =
         update_stack_visible_in_treeview(regex, stack->callees[icallee]);
      stack->visible_in_treeview = child_visible || stack->visible_in_treeview;
   }

   // if it is not determined whether this stack will be visible
   // use lazy evaluation to prevent useless execution of strstr
   stack->visible_in_treeview = stack->visible_in_treeview ||
      (regexec(regex, stack->name, 0, NULL, 0) == 0);

   return stack->visible_in_treeview;
}

// precompute the visibility of each stack
// so that the actual visibility function
// can simply lookup the value, instead
// of computing it in exponential time.
bool update_stack_visible_in_listview(regex_t *regex,
                                      vfd_stack_entry_t *stack) {
   // a stack should only be visible if 
   // its function name matches the regular expression
   stack->visible_in_listview = regexec(regex, stack->name, 0, NULL, 0) == 0;

   return stack->visible_in_listview;
}

void free_vfd_stacks(unsigned int nstacks, vfd_stack_entry_t *stacks) {
   for (unsigned int istack=0; istack<nstacks; istack++) {
      stacks[istack].ID = 0;
      stacks[istack].level = 0;
      stacks[istack].callerID = 0;
      stacks[istack].caller = NULL;
      for (int icallee=0; icallee<stacks[istack].ncallees; icallee++) {
         free(stacks[istack].callees);
         stacks[istack].callees = NULL;
      }
      stacks[istack].ncallees = 0;
      free(stacks[istack].callees);
      stacks[istack].callees = NULL;
      stacks[istack].precise = false;
      stacks[istack].namelen = 0;
      free(stacks[istack].name);
      stacks[istack].name = NULL;
   }

   free(stacks);
}

void print_vfd_stacks(vfd_header_t *header, vfd_stack_entry_t *stacks) {
   unsigned int nstacks = header->stackscount;
   fprintf(stderr, "VFD-Stacks:\n");
   for (unsigned int istack=0; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = stacks+istack;
      fprintf(stderr, "   ID:             %d\n", stack_ptr->ID);
      fprintf(stderr, "      Name         %s\n", stack_ptr->name);
      fprintf(stderr, "      Level        %d\n", stack_ptr->level);
      fprintf(stderr, "      Precise      %s\n", stack_ptr->precise ? "true" : "false");
      fprintf(stderr, "      Caller ID:   %d\n", stack_ptr->callerID);
      fprintf(stderr, "      Caller name: %s\n", stack_ptr->caller->name);
      fprintf(stderr, "      Callees:     %d\n", stack_ptr->ncallees);
      for (int icallee=0; icallee < stack_ptr->ncallees; icallee++) {
         fprintf(stderr, "         %s\n", stack_ptr->callees[icallee]->name);
      }
   }
}

