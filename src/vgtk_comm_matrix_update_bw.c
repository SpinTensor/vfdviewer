#include "vfd_types.h"
#include "vfd_list.h"
#include "vgtk_stacktimeline_entry.h"
#include "vgtk_comm_matrix_legend.h"

void comm_matrix_update_bw_max(int nprocs, double *matrix) {
   if (nprocs == 0) {return;}
   double tmin = get_tmin_stacktimeline_draw();
   double tmax = get_tmax_stacktimeline_draw();

   // Zero the bandwidth comm matrix
   for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
      matrix[iproc] = 0.0;
   }

   double maxbw = 0.0;
   // loop over all vfd-traces
   vfd_t *vfdtrace = first_vfd();
   while (vfdtrace != NULL) {
      int myrank = vfdtrace->header->myrank;
      // go through all message samples of this vfd-trace
      // and search for the maximum bandwidth for the spcific
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
            matrix[idx] = 
               matrix[idx] > message.rate_MiBs ?
                  matrix[idx] :
                  message.rate_MiBs;

            // update the maximum bandwidth for normalization
            maxbw = maxbw > message.rate_MiBs ? maxbw : message.rate_MiBs;
         }
      }

      // go to the next vfd trace
      vfdtrace = vfdtrace->next;
   }

   // normalize the matrix
   if (maxbw > 0.0) {
      for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
         matrix[iproc] /= maxbw;
      }
   } else {
      maxbw = 1.0;
   }

   // update the legend labels
   set_comm_matrix_bw_label_max_value(maxbw);
   set_comm_matrix_bw_label_mid_value(0.5*maxbw);
   set_comm_matrix_bw_label_min_value(0.0);
}
void comm_matrix_update_bw_avg(int nprocs, double *matrix) {
   if (nprocs == 0) {return;}
   unsigned int *count = (unsigned int*) malloc(nprocs*nprocs*sizeof(unsigned int));
   double tmin = get_tmin_stacktimeline_draw();
   double tmax = get_tmax_stacktimeline_draw();

   // Zero the bandwidth comm matrix
   for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
      matrix[iproc] = 0.0;
      count[iproc] = 0;
   }

   // loop over all vfd-traces
   vfd_t *vfdtrace = first_vfd();
   while (vfdtrace != NULL) {
      int myrank = vfdtrace->header->myrank;
      // go through all message samples of this vfd-trace
      // and search for the maximum bandwidth for the spcific
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
            matrix[idx] += message.rate_MiBs;
            count[idx]++;
         }
      }

      // go to the next vfd trace
      vfdtrace = vfdtrace->next;
   }

   // compute average from accumulated values
   for (int iproc=1; iproc<nprocs*nprocs; iproc++) {
      if (count[iproc] > 0) {
         matrix[iproc] /= (double) count[iproc];
      }
   }

   // normalize the matrix
   // search for maximum bandwidth
   double maxbw = matrix[0];
   for (int iproc=1; iproc<nprocs*nprocs; iproc++) {
      maxbw = maxbw > matrix[iproc] ?
         maxbw : matrix[iproc];
   }
   if (maxbw > 0.0) {
      for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
         matrix[iproc] /= maxbw;
      }
   } else {
      maxbw = 1.0;
   }

   free(count);
   count = NULL;

   // update the legend labels
   set_comm_matrix_bw_label_max_value(maxbw);
   set_comm_matrix_bw_label_mid_value(0.5*maxbw);
   set_comm_matrix_bw_label_min_value(0.0);
}
void comm_matrix_update_bw_min(int nprocs, double *matrix) {
   if (nprocs == 0) {return;}
   double tmin = get_tmin_stacktimeline_draw();
   double tmax = get_tmax_stacktimeline_draw();

   // Zero the bandwidth comm matrix
   for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
      matrix[iproc] = -1.0;
   }

   // loop over all vfd-traces
   vfd_t *vfdtrace = first_vfd();
   while (vfdtrace != NULL) {
      int myrank = vfdtrace->header->myrank;
      // go through all message samples of this vfd-trace
      // and search for the maximum bandwidth for the spcific
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
            if (matrix[idx] < 0.0) {
               matrix[idx] = message.rate_MiBs;
            } else {
               matrix[idx] = 
                  matrix[idx] < message.rate_MiBs ?
                     matrix[idx] :
                     message.rate_MiBs;
            }
         }
      }

      // go to the next vfd trace
      vfdtrace = vfdtrace->next;
   }

   // normalize the matrix
   // search for maximum bandwidth
   double maxbw = matrix[0];
   for (int iproc=1; iproc<nprocs*nprocs; iproc++) {
      maxbw = maxbw > matrix[iproc] ?
         maxbw : matrix[iproc];
   }
   if (maxbw > 0.0) {
      for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
         if (matrix[iproc] < 0.0) {
            matrix[iproc] = 0.0;
         } else {
            matrix[iproc] /= maxbw;
         }
      }
   } else {
      maxbw = 1.0;
   }

   // update the legend labels
   set_comm_matrix_bw_label_max_value(maxbw);
   set_comm_matrix_bw_label_mid_value(0.5*maxbw);
   set_comm_matrix_bw_label_min_value(0.0);
}
