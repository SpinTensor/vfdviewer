#include <vfd_types.h>

#define SHELL_NGAPS 8
#define SHELL_GAPS {701,30,1132,57,23,10,4,1}

void shellsort_messages(unsigned int nmsg, vfd_message_t *messages) {
   const int ngaps = SHELL_NGAPS;
   const int gaps[SHELL_NGAPS] = SHELL_GAPS;

   // repeat the sort for each gap
   // start with the largest and work down to 1
   for (int igap=0; igap< ngaps; igap++) {
      int gap = gaps[igap];
      // Do a gapped insertion sort for this gap size.
      // The first gap elements a[0..gap-1] are already in gapped order
      // keep adding one more element until the entire array is gap sorted
      for (unsigned int imsg=gap; imsg<nmsg; imsg++) {
         // add a[i] to the elements that have been gap sorted
         // save a[i] in temp and make a hole at position i
         vfd_message_t tmpmsg = messages[imsg];
         // shift earlier gap-sorted elements up
         // until the correct location for a[i] is found
         unsigned int jmsg=imsg; 
         while (jmsg>gap && messages[jmsg-gap].tstart_usec > tmpmsg.tstart_usec) {
            messages[jmsg] = messages[jmsg - gap];
            jmsg -= gap;
         }
         // put temp (the original a[i]) in its correct location
         messages[jmsg] = tmpmsg;
      }
   }
}

#undef SHELL_NGAPS
#undef SHELL_GAPS
