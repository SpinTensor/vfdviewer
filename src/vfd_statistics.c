#include "vfd_types.h"

void vfd_create_stack_statistics(unsigned int fcallscount, vfd_fcall_t *fcalls,
                                 vfd_stack_entry_t *stacks) {

   // go over all constructed function calls
   // and count how often each stack was called
   // and the exclusive and inclusive time
   // in the stack
   for (unsigned int ifcall=0; ifcall<fcallscount; ifcall++) {
      // increment stack call counter
      int stackID = fcalls[ifcall].stackID;
      stacks[stackID].num_called++;
      // also increment the calls counter
      // of the parent stack
      stacks[stackID].caller->num_calls++;

      // add the passed time to the 
      // time counters
      double deltat = fcalls[ifcall].exit_time - fcalls[ifcall].entry_time;
      stacks[stackID].excl_time += deltat;
      stacks[stackID].incl_time += deltat;

      // subtrac the passed time from the calles exclusive time
      stacks[stackID].caller->excl_time -= deltat;
   }
}
