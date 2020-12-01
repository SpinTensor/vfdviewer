#include <stdlib.h>
#include <stdio.h>

#include "vfd_types.h"
void print_current_fcalls(int ilevel, vfd_fcall_t *curr_stack);

void store_vfcall(int *ilevel, vfd_fcall_t *curr_stack,
                  int *nfcalls, int *maxfcalls, vfd_fcall_t **fcalls) {
   // first check if the array is large enough to hold one more entry
   if (*nfcalls == *maxfcalls) {
      // no more space. reallocate.
      int newmaxfcalls = (int) (1.2* (*maxfcalls));
      vfd_fcall_t *tmp_fcalls = (vfd_fcall_t*) malloc(newmaxfcalls*sizeof(vfd_fcall_t));
      // transfer the data
      for (int ifcall=0; ifcall<*nfcalls; ifcall++) {
         tmp_fcalls[ifcall] = (*fcalls)[ifcall];
      }
      // free old memory
      free(*fcalls);
      // transfer pointer
      *fcalls = tmp_fcalls;
      *maxfcalls = newmaxfcalls;
   }

   // transfer the top of the current stack to the permanent storage
   (*fcalls)[*nfcalls] = curr_stack[*ilevel];
   (*nfcalls)++;
   (*ilevel)--;
}

void buildup_stack(int stackID, long long t0,
                   vfd_stack_entry_t *stacks,
                   int *ilevel, vfd_fcall_t *curr_stack) {
   // get the newlevel and fill the current stack
   int newilevel = stacks[stackID].level;
   int oldilevel = *ilevel;
   if (newilevel > oldilevel) {
      // fill in the stacks up to this level
      for (int jlevel=newilevel; jlevel>oldilevel; jlevel--) {
         curr_stack[jlevel].stackID = stackID;
         stackID = stacks[stackID].callerID;
      }
      // assume all parent functions started at t0
      // set exit time to an invalid -1
      for (int jlevel=oldilevel+1; jlevel<newilevel; jlevel++) {
         curr_stack[jlevel].entry_time = t0;
         curr_stack[jlevel].exit_time = -1ll;
      }
      *ilevel = newilevel-1;
   }
}

void buildup_stackhead(int stackID, long long t1,
                       vfd_stack_entry_t *stacks,
                       int *ilevel, vfd_fcall_t *curr_stack) {
   // get the newlevel and fill the current stack
   int newilevel = stacks[stackID].level;

   // the sampled function gets t1 as entry time
   curr_stack[newilevel].entry_time = t1;
   curr_stack[newilevel].exit_time = -1ll;

   *ilevel = newilevel;
}

void dismantle_stack(int stackID, long long t0,
                     vfd_stack_entry_t *stacks,
                     int *ilevel, vfd_fcall_t *curr_stack,
                     int *nfcalls, int *maxfcalls, vfd_fcall_t **fcalls) {

   // get the new level and 
   int newilevel = stacks[stackID].level;
   int oldilevel = *ilevel;

   if (newilevel < oldilevel) {
      // fill in the exit time as t0
      // and store away the finished functions
      for (int jlevel=oldilevel; jlevel>newilevel; jlevel--) {
         curr_stack[jlevel].exit_time = t0;
         int tmpilevel = jlevel;
         // store away the finished function
         store_vfcall(&tmpilevel, curr_stack,
                      nfcalls, maxfcalls, fcalls);
      }
      *ilevel = newilevel;
   }
}

void dismantle_stackhead(int stackID, long long t1,
                         vfd_stack_entry_t *stacks,
                         int *ilevel, vfd_fcall_t *curr_stack,
                         int *nfcalls, int *maxfcalls, vfd_fcall_t **fcalls) {

   // get the new level and 
   int newilevel = stacks[stackID].level;

   // fill in the exit time of the sampled function as t1
   // and store away the finished function
   curr_stack[newilevel].exit_time = t1;
   int tmpilevel = newilevel;
   // store away the finished function
   store_vfcall(&tmpilevel, curr_stack,
                nfcalls, maxfcalls, fcalls);
   *ilevel = newilevel - 1;
}

// search for the closest common stack
// that both stacks originated from
int closest_common_stack(vfd_stack_entry_t *stacks,
                         int stackID1, int stackID2) {

   // first step is to bring both stacks on the same level
   while (stacks[stackID1].level > stacks[stackID2].level) {
      stackID1 = stacks[stackID1].callerID;
   }
   while (stacks[stackID2].level > stacks[stackID1].level) {
      stackID2 = stacks[stackID2].callerID;
   }
   // Now reduce the stack IDs in their level
   // until they are equal. 
   // They will have found the closest common stack
   while (stackID1 != stackID2) {
      stackID1 = stacks[stackID1].callerID;
      stackID2 = stacks[stackID2].callerID;
   }

   return stackID1;
}

void construct_vfd_fcalls(vfd_t *vfd) {
   // create the structure to hold the final callhistory
   // might need to be reallocated. 
   int maxfcalls = vfd->header->function_samplecount;
   // needs to be at least 16 
   maxfcalls = maxfcalls < 16 ? 16 : maxfcalls;
   int nfcalls = 0;
   vfd_fcall_t *fcalls = (vfd_fcall_t*) malloc(maxfcalls*sizeof(vfd_fcall_t));

   // create a structure to hold the current stack
   vfd_fcall_t *curr_stack;
   curr_stack = (vfd_fcall_t*)
      malloc((vfd->maxlevel+1)*sizeof(vfd_fcall_t));

   vfd_stack_sample_t *stack_samples = vfd->stack_samples;
   vfd_stack_entry_t *stacks = vfd->stacks;

   int ilevel = -1;
   // Add first stack by hand
   // As it need special treatment
   // due to the empty stack
   vfd_stack_sample_t sample;
   sample = stack_samples[0];
   if (sample.kind == fnct_entry) {
      // only need to build up the stack
      buildup_stack(sample.stackID, 0ll,
                    stacks, &ilevel, curr_stack);
      buildup_stackhead(sample.stackID, sample.sampletime,
                        stacks, &ilevel, curr_stack);
   } else {
      // first build up the stack
      // then dismantle the top function
      buildup_stack(sample.stackID, 0ll,
                    stacks, &ilevel, curr_stack);
      buildup_stackhead(sample.stackID, 0ll,
                        stacks, &ilevel, curr_stack);
      dismantle_stackhead(sample.stackID, sample.sampletime,
                          stacks, &ilevel, curr_stack,
                          &nfcalls, &maxfcalls, &fcalls);
   }

#ifdef _DEBUG
   fprintf(stderr, "Stack-sample %u\n", 0);
   fprintf(stderr, "%16.6lf", sample.sampletime*1.0e-6);
   fprintf(stderr, " %s", sample.kind == fnct_entry ? "call" : "exit");
   fprintf(stderr, " stackID=%d\n", sample.stackID);
   print_current_fcalls(ilevel, curr_stack);
#endif 

   // save the last time for time estimates
   long long lastsampletime = sample.sampletime;
   // go through all stack samples and reconstruct the function calls
   for (unsigned int isample=1; isample<vfd->header->function_samplecount; isample++) {
      // current stack already has entries
      // get the next sample
      sample = stack_samples[isample];
      // as it is not available estimate the time of events 
      // since the last sample
      long long timeestimate;
      timeestimate = lastsampletime + sample.sampletime;
      timeestimate *=0.5;
      lastsampletime = sample.sampletime;
      // compute the closest common stack
      // between the current stackhead
      // and the new stack sample
      int ccstackID = closest_common_stack(stacks,
                                           curr_stack[ilevel].stackID,
                                           sample.stackID);

      // dismantle everything above the common stack.
      // if the closest common stack is the sampled stack itself,
      // or the current stack head is the common stack, 
      // nothing will be done.
      dismantle_stack(ccstackID, timeestimate,
                      stacks, &ilevel, curr_stack,
                      &nfcalls, &maxfcalls, &fcalls);

      // build up stack until it reaches the sampled stack
      // if the current stack head is already equal the the sampled stack
      // nothing will be done
      buildup_stack(sample.stackID, timeestimate,
                    stacks, &ilevel, curr_stack);

      if (sample.kind == fnct_exit) {
         // if the current stack head and the sampel stack are
         // different the stack head needs to be constructed
         if (sample.stackID != curr_stack[ilevel].stackID) {
            buildup_stackhead(sample.stackID, timeestimate,
                              stacks, &ilevel, curr_stack);
         }
         // if the sample is a function exit dismantle the current head stack
         dismantle_stackhead(sample.stackID, sample.sampletime,
                             stacks, &ilevel, curr_stack,
                             &nfcalls, &maxfcalls, &fcalls);
      } else {
         // if the sample is a function entry build new head stack
         buildup_stackhead(sample.stackID, sample.sampletime,
                           stacks, &ilevel, curr_stack);
      }
#ifdef _DEBUG
      fprintf(stderr, "Stack-sample %u\n", isample);
      fprintf(stderr, "%16.6lf", sample.sampletime*1.0e-6);
      fprintf(stderr, " %s", sample.kind == fnct_entry ? "call" : "exit");
      fprintf(stderr, " stackID=%d\n", sample.stackID);
      print_current_fcalls(ilevel, curr_stack);
      fprintf(stderr, "\n");
#endif
   }

   free(curr_stack);
   curr_stack = NULL;

   vfd->header->fcallscount = nfcalls;
   vfd->fcalls = fcalls;
}

void free_vfd_fcalls(unsigned int nfcalls, vfd_fcall_t *fcalls) {
   (void) nfcalls;
   free(fcalls);
}

void print_current_fcalls(int ilevel, vfd_fcall_t *curr_stack) {
   for (int jlevel=0; jlevel<=ilevel; jlevel++) {
      printf("Start = %16.6fs, End = %16.6fs, StackID = %d\n",
             curr_stack[jlevel].entry_time*1.0e-6,
             curr_stack[jlevel].exit_time*1.0e-6,
             curr_stack[jlevel].stackID);
   }
}

void print_vfd_fcalls(vfd_header_t *header, vfd_fcall_t *fcalls) {
   fprintf(stderr, "VFD calling timeline:\n");
   unsigned int fcallscount = header->fcallscount;
   for (unsigned int ifcall=0; ifcall<fcallscount; ifcall++) {
      fprintf(stderr, "%16.6lf", fcalls[ifcall].entry_time*1.0e-6);
      fprintf(stderr, " Call StackID %d\n", fcalls[ifcall].stackID);
      fprintf(stderr, "%16.6lf", fcalls[ifcall].exit_time*1.0e-6);
      fprintf(stderr, " Exit StackID %d\n", fcalls[ifcall].stackID);
   }
}

