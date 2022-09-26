#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>

#include "vfd_types.h"
#include "vfd_stacks.h"
#include "vgtk_colors.h"
#include "hashing.h"

bool is_precise (char *s) {
   return s[strlen(s)-1] == '*';
}

void read_vfd_stacks(FILE *vfd_file, vfd_header_t *header,
                      vfd_stack_entry_t **stacks_ptr, int *maxlevel) {
   unsigned int nstacks = header->nstacks;
   *maxlevel = 0;

   *stacks_ptr = (vfd_stack_entry_t*) malloc(nstacks*sizeof(vfd_stack_entry_t));
   vfd_stack_entry_t *stacks = *stacks_ptr;
   memset((void*) stacks, 0, nstacks*sizeof(vfd_stack_entry_t));

   // Read in the vfd information
   fseek(vfd_file, header->stacks_offset, SEEK_SET);

   // first stack needs special treatment
   stacks[0].ID = 0;
   stacks[0].level = 0;
   stacks[0].callerID = 0;
   stacks[0].caller = NULL;
   stacks[0].ncallees = 0;
   stacks[0].callees = NULL;
   stacks[0].threadID = 0;
   stacks[0].precise = false;
   stacks[0].namelen = 0;
   stacks[0].name = NULL;
   stacks[0].num_called = 0;
   stacks[0].num_calls = 0;
   stacks[0].excl_time = 0.0;
   stacks[0].incl_time = 0.0;
   stacks[0].visible_in_treeview = true;
   stacks[0].visible_in_listview = true;
   
   size_t read_elem;
   read_elem = fread(&(stacks[0].callerID), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading first stacks caller\n");
      exit(EXIT_FAILURE);
   }
   stacks[0].callerID = 0;
   read_elem = fread(&(stacks[0].namelen), sizeof(int), 1, vfd_file);
   if (read_elem != 1) {
      fprintf(stderr, "Error in reading first stacks namelen\n");
      exit(EXIT_FAILURE);
   }
   stacks[0].name = (char*) malloc(stacks[0].namelen*sizeof(char));
   read_elem = fread(stacks[0].name, sizeof(char), stacks[0].namelen, vfd_file);
   if (read_elem != (size_t)stacks[0].namelen) {
      fprintf(stderr, "Error in reading first stacks name\n");
      exit(EXIT_FAILURE);
   }

   // all other stacks
   for (unsigned int istack=1; istack<nstacks; istack++) {
      stacks[istack].ID = istack;
      stacks[istack].level = 0;
      stacks[istack].callerID = 0;
      stacks[istack].caller = NULL;
      stacks[istack].ncallees = 0;
      stacks[istack].callees = NULL;
      stacks[istack].threadID = 0;
      stacks[istack].precise = false;
      stacks[istack].namelen = 0;
      stacks[istack].name = NULL;
      stacks[istack].num_called = 0;
      stacks[istack].num_calls = 0;
      stacks[istack].excl_time = 0.0;
      stacks[istack].incl_time = 0.0;
      stacks[istack].visible_in_treeview = true;
      stacks[istack].visible_in_listview = true;
      read_elem = fread(&(stacks[istack].callerID), sizeof(int), 1, vfd_file);
      if (read_elem != 1) {
         fprintf(stderr, "Error in reading stacks[%d] caller\n", istack);
         exit(EXIT_FAILURE);
      }
      read_elem = fread(&(stacks[istack].namelen), sizeof(int), 1, vfd_file);
      if (read_elem != 1) {
         fprintf(stderr, "Error in reading first stacks[%d] namelen\n", istack);
         exit(EXIT_FAILURE);
      }
      stacks[istack].name = (char*) malloc(stacks[istack].namelen*sizeof(char));
      read_elem = fread(stacks[istack].name, sizeof(char),
                        stacks[istack].namelen, vfd_file);
      if (read_elem != (size_t)stacks[istack].namelen) {
         fprintf(stderr, "Error in reading first stacks[%d] name\n", istack);
         exit(EXIT_FAILURE);
      }
   }

   // Derive the remaining properties of the stacks
   for (unsigned int istack=0; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = stacks+istack;
      // if the function is precise
      stack_ptr->precise = is_precise(stack_ptr->name);
      stack_ptr->namelen--;
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
      for (int icallee=0; icallee<caller->ncallees; icallee++) {
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

   // determine the call depth
   for (unsigned int istack=1; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = stacks+istack;
      vfd_stack_entry_t *caller = stack_ptr->caller;
      stack_ptr->level = caller->level+1;
      if (stack_ptr->level > *maxlevel) {
         *maxlevel = stack_ptr->level;
      }
   }
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

int get_stack_string_length(vfd_stack_entry_t *stack) {
   int stackstrlength = stack->namelen;
   vfd_stack_entry_t *stackroot = stack-stack->ID;
   vfd_stack_entry_t *tmpstack = stack;
   // go down the stack until the bottom is reached
   // record the length of the function names each
   while (tmpstack->callerID) {
      tmpstack = stackroot+tmpstack->callerID;
      // add one chars for function division by "<"
      stackstrlength += 1;
      stackstrlength += tmpstack->namelen;
   }

   return stackstrlength;
}

char *get_stack_string(vfd_stack_entry_t *stack) {
   // determine the length of the stack string
   int stackstrlength = get_stack_string_length(stack);

   // allocate space to hold the complete string
   char *stackstring = (char*) malloc((1+stackstrlength)*sizeof(char));
   char *strptr = stackstring;
   // copy the first string in and move the strpointer forward
   strcpy(strptr, stack->name);
   strptr += strlen(stack->name);
   // go down the stack until the bottom is reached
   // copy the function names onto the string
   vfd_stack_entry_t *stackroot = stack-stack->ID;
   vfd_stack_entry_t *tmpstack = stack;
   while (tmpstack->callerID) {
      tmpstack = stackroot+tmpstack->callerID;;
      strcpy(strptr, "<");
      strptr += 1;
      strcpy(strptr, tmpstack->name);
      strptr += strlen(tmpstack->name);
   }
   return stackstring;
}

void print_vfd_stacks(vfd_header_t *header, vfd_stack_entry_t *stacks) {
   unsigned int nstacks = header->nstacks;
   fprintf(stderr, "VFD-Stacks:\n");
   for (unsigned int istack=0; istack<nstacks; istack++) {
      vfd_stack_entry_t *stack_ptr = stacks+istack;
      fprintf(stderr, "   ID:             %d\n", stack_ptr->ID);
      fprintf(stderr, "      Namelen      %d\n", stack_ptr->namelen);
      fprintf(stderr, "      Name         %s\n", stack_ptr->name);
      fprintf(stderr, "      Level        %d\n", stack_ptr->level);
      fprintf(stderr, "      Precise      %s\n", stack_ptr->precise ? "true" : "false");
      fprintf(stderr, "      Caller ID:   %d\n", stack_ptr->callerID);
      fprintf(stderr, "      Caller name: %s\n", stack_ptr->caller->name);
      fprintf(stderr, "      Callees:     %d\n", stack_ptr->ncallees);
      for (int icallee=0; icallee < stack_ptr->ncallees; icallee++) {
         fprintf(stderr, "         %s\n", stack_ptr->callees[icallee]->name);
      }
      fprintf(stderr, "      DrawColor:   %5.1lf %5.1lf %5.1lf\n",
              stack_ptr->drawcolor.red,
              stack_ptr->drawcolor.green,
              stack_ptr->drawcolor.blue);
   }
}

