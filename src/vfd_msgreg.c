#include <stdlib.h>
#include <stdio.h>

#include <math.h>

#include "vfd_types.h"

void store_current_msgreg(vfd_msgreg_t *msgreg, int *nmsgregs,
                          int *maxmsgregs, vfd_msgreg_t **msgregs) {
   // first check if the array is large enough to hold one more entry
   if (*nmsgregs == *maxmsgregs) {
      // no more space. reallocate
      int newmaxmsgregs = (int) (1.2 * (*maxmsgregs));
      vfd_msgreg_t *tmp_msgregs =
         (vfd_msgreg_t*) malloc(newmaxmsgregs*sizeof(vfd_msgreg_t));
      // transfer the data
      for (int imsgreg=0; imsgreg<*nmsgregs; imsgreg++) {
         tmp_msgregs[imsgreg] = (*msgregs)[imsgreg];
      }
      // free old memory
      free(*msgregs);
      // transfer pointer
      *msgregs = tmp_msgregs;
      *maxmsgregs = newmaxmsgregs;
   }

   // transfer the message_region to the permant storage
   (*msgregs)[*nmsgregs] = *msgreg;
   (*nmsgregs)++;

   // invalidate message region
   msgreg->entry_time = -1.0;
   msgreg->exit_time = -1.0;
}

void construct_vfd_msgregs(vfd_t *vfd) {
   // create the structure to hold the final message regions
   int maxmsgregs_send = 1024;
   int maxmsgregs_recv = 1024;
   int nmsgregs_send = 0;
   int nmsgregs_recv = 0;

   vfd_msgreg_t *msgregs_send =
      (vfd_msgreg_t*) malloc(maxmsgregs_send*sizeof(vfd_msgreg_t));
   vfd_msgreg_t *msgregs_recv =
      (vfd_msgreg_t*) malloc(maxmsgregs_recv*sizeof(vfd_msgreg_t));

   // create structure to hold current message region
   vfd_msgreg_t msgreg_send;
   msgreg_send.entry_time = -1.0;
   msgreg_send.exit_time = -1.0;
   vfd_msgreg_t msgreg_recv;
   msgreg_recv.entry_time = -1.0;
   msgreg_recv.exit_time = -1.0;

   // loop over all message samples and attempt to group them
   for (unsigned int imsg=0; imsg<vfd->header->message_samplecount; imsg++) {
      vfd_message_sample_t *msgsample = (vfd->message_samples)+imsg;

      // assign pointers based on the message sample direction
      // to reduce redundant code
      int *cur_maxmsgregs;
      int *cur_nmsgregs;
      vfd_msgreg_t **cur_msgregs;
      vfd_msgreg_t *cur_msgreg;

      if (msgsample->dir == send) {
         cur_maxmsgregs = &maxmsgregs_send;
         cur_nmsgregs = &nmsgregs_send;
         cur_msgregs = &msgregs_send;
         cur_msgreg = &msgreg_send;
      } else {
         cur_maxmsgregs = &maxmsgregs_recv;
         cur_nmsgregs = &nmsgregs_recv;
         cur_msgregs = &msgregs_recv;
         cur_msgreg = &msgreg_recv;
      }

      if (cur_msgreg->entry_time < 0.0) {
         // if the current message region is empty
         // fill it with the message sample
         cur_msgreg->entry_time = msgsample->dtstart_sec;
         cur_msgreg->exit_time = msgsample->dtend_sec;
      } else {
         // check if the sample overlaps with the current message region
         // or if they are closer than 10usec
         if (msgsample->dtstart_sec < cur_msgreg->exit_time ||
            // if so fuse them into one. 
             fabs(msgsample->dtstart_sec-cur_msgreg->exit_time) < 1.0e-5) {
            cur_msgreg->exit_time = msgsample->dtend_sec;
         } else {
            // no overlap and no fuse potential
            // store away the old region and open a new one
            store_current_msgreg(cur_msgreg, cur_nmsgregs,
                                 cur_maxmsgregs, cur_msgregs);
            cur_msgreg->entry_time = msgsample->dtstart_sec;
            cur_msgreg->exit_time = msgsample->dtend_sec;
         }
      }
   }

   vfd->header->msgregsendcount = nmsgregs_send;
   vfd->header->msgregrecvcount = nmsgregs_recv;
   // reallocate one last time to match the actual number of entries
   vfd_msgreg_t *tmpmsgregs;
   tmpmsgregs = (vfd_msgreg_t*) malloc(nmsgregs_send*sizeof(vfd_msgreg_t));
   for (int imsgreg=0; imsgreg<nmsgregs_send; imsgreg++) {
      tmpmsgregs[imsgreg] = msgregs_send[imsgreg];
   }
   free(msgregs_send);
   msgregs_send = tmpmsgregs;

   tmpmsgregs = (vfd_msgreg_t*) malloc(nmsgregs_recv*sizeof(vfd_msgreg_t));
   for (int imsgreg=0; imsgreg<nmsgregs_recv; imsgreg++) {
      tmpmsgregs[imsgreg] = msgregs_recv[imsgreg];
   }
   free(msgregs_recv);
   msgregs_recv = tmpmsgregs;
   tmpmsgregs = NULL;

   vfd->msgregs_send = msgregs_send;
   vfd->msgregs_recv = msgregs_recv;
}

void free_vfd_msgregs(unsigned int nmsgregs, vfd_msgreg_t *msgregs) {
   (void) nmsgregs;
   free(msgregs);
}

void print_vfd_msgregs(vfd_header_t *header,
                       vfd_msgreg_t *msgregs_send,
                       vfd_msgreg_t *msgregs_recv) {
   fprintf(stderr, "VFD Message send regions\n");
   for (unsigned int imsgreg=0; imsgreg<header->msgregsendcount; imsgreg++) {
      fprintf(stderr, "   send(%u): %16.6lf - %16.6lf\n",
              imsgreg,
              msgregs_send[imsgreg].entry_time,
              msgregs_send[imsgreg].exit_time);
   }
   fprintf(stderr, "\n");
   fprintf(stderr, "VFD Message recv regions\n");
   for (unsigned int imsgreg=0; imsgreg<header->msgregrecvcount; imsgreg++) {
      fprintf(stderr, "   recv(%u): %16.6lf - %16.6lf\n",
              imsgreg,
              msgregs_recv[imsgreg].entry_time,
              msgregs_recv[imsgreg].exit_time);
   }
   fprintf(stderr, "\n");
}
