#include <stdbool.h>

#include "vfd_types.h"
#include "vfd_list.h"
#include "vgtk_types.h"
#include "vgtk_stacktimeline_entry.h"
#include "vgtk_comm_matrix_mode_switcher.h"

void comm_matrix_update_count(vgtk_comm_matrix_t *comm_matrix) {
   if (comm_matrix->nprocs == 0) {return;}
   int nprocs = comm_matrix->nprocs;
   double tmin = get_tmin_stacktimeline_draw();
   double tmax = get_tmax_stacktimeline_draw();

   bool show_send = comm_matrix_direction_send_checked();
   bool show_recv = comm_matrix_direction_recv_checked();

   // Zero the count comm matrix
   for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
      comm_matrix->data[iproc] = 0.0;
      comm_matrix->entry_valid[iproc] = false;
   }

   // loop over all vfd-traces
   vfd_t *vfdtrace = first_vfd();
   while (vfdtrace != NULL) {
      int myrank = vfdtrace->header->myrank;
      // go through all message samples of this vfd-trace
      // and count the messages for the spcific
      // combination of sender and receiver
      unsigned int nmsg = vfdtrace->header->message_samplecount;
      for (unsigned int imsg=0; imsg<nmsg; imsg++) {
         vfd_message_sample_t message = vfdtrace->message_samples[imsg];
         if (message.dtstart_sec > tmax) {
            // only update matrix until the first message sample later
            // than the max_drawtime of the stacktimeline is encountered.
            // They are sorted, thus no one should be forgotten.
            break;
         } else if (message.dtend_sec > tmin) {
            // only update matrix if the end time
            // falls into the selected time window

            if ((show_send && message.dir == send) ||
                (show_recv && message.dir == recv)) {
               int icol;
               int irow;
               if (message.dir == send) {
                  icol = myrank;
                  irow = message.rank;
               } else {
                  icol = message.rank;
                  irow = myrank;
               }
   
               // update the matrix entry
               int idx = irow*nprocs + icol;
               comm_matrix->data[idx] += 1.0;
               comm_matrix->entry_valid[idx] = true;
            }
         }
      }

      // go to the next vfd trace
      vfdtrace = vfdtrace->next;
   }

   // normalize the matrix
   // search for maximum / minimum count
   //
   // first find the first valid entry
   comm_matrix->any_entry_valid = false;
   int first_valid = -1;
   for (int idx=0; idx<nprocs*nprocs; idx++) {
      if (comm_matrix->entry_valid[idx]) {
         comm_matrix->any_entry_valid = true;
         first_valid = idx;
         break;
      }
   }

   // now start the actual search
   if (comm_matrix->any_entry_valid) {
      comm_matrix->maxval = comm_matrix->data[first_valid];
      comm_matrix->minval = comm_matrix->data[first_valid];

      for (int idx=first_valid; idx<nprocs*nprocs; idx++) {
         if (comm_matrix->data[idx] > comm_matrix->maxval) {
            comm_matrix->maxval = comm_matrix->data[idx];
         } else if (comm_matrix->data[idx] < comm_matrix->minval) {
            comm_matrix->minval = comm_matrix->data[idx];
         }
      }
   }
}
