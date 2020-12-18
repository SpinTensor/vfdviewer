#include "vfd_types.h"
#include "vfd_list.h"
#include "vgtk_stacktimeline_entry.h"
#include "vgtk_comm_matrix_legend.h"

void comm_matrix_update_count(int nprocs, double *matrix) {
   if (nprocs == 0) {return;}
   double tmin = get_tmin_stacktimeline_draw();
   double tmax = get_tmax_stacktimeline_draw();

   // Zero the bandwidth comm matrix
   for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
      matrix[iproc] = 0.0;
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
            matrix[idx] += 1.0;
         }
      }

      // go to the next vfd trace
      vfdtrace = vfdtrace->next;
   }

   // normalize the matrix
   // search for maximum count
   double maxcount = matrix[0];
   for (int iproc=1; iproc<nprocs*nprocs; iproc++) {
      maxcount = maxcount > matrix[iproc] ?
         maxcount : matrix[iproc];
   }
   if (maxcount > 0.0) {
      for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
         matrix[iproc] /= maxcount;
      }
   } else {
      maxcount = 1.0;
   }

   // update the legend labels
   set_comm_matrix_label_max_value(maxcount);
   set_comm_matrix_label_mid_value(0.5*maxcount);
   set_comm_matrix_label_min_value(0.0);
}
