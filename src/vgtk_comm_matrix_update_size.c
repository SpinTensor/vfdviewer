#include <stdbool.h>

#include "vfd_types.h"
#include "vfd_list.h"
#include "vgtk_stacktimeline_entry.h"
#include "vgtk_comm_matrix_legend.h"
#include "vgtk_comm_matrix_mode_switcher.h"

void comm_matrix_update_size_max(int nprocs, double *matrix) {
   if (nprocs == 0) {return;}
   double tmin = get_tmin_stacktimeline_draw();
   double tmax = get_tmax_stacktimeline_draw();

   bool show_send = comm_matrix_direction_send_checked();
   bool show_recv = comm_matrix_direction_recv_checked();

   // Zero the bandwidth comm matrix
   for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
      matrix[iproc] = 0.0;
   }

   double maxsize = 0.0;
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
               double size = message.count * message.typeSize / 1024.0 / 1024.0;
               matrix[idx] = 
                  matrix[idx] > size ?
                     matrix[idx] :
                     size;

               // update the maximum bandwidth for normalization
               maxsize = maxsize > size ? maxsize : size;
            }
         }
      }

      // go to the next vfd trace
      vfdtrace = vfdtrace->next;
   }

   // normalize the matrix
   if (maxsize > 0.0) {
      for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
         matrix[iproc] /= maxsize;
      }
   } else {
      maxsize = 1.0;
   }

   // update the legend labels
   set_comm_matrix_label_max_value(maxsize);
   set_comm_matrix_label_mid_value(0.5*maxsize);
   set_comm_matrix_label_min_value(0.0);
}
void comm_matrix_update_size_avg(int nprocs, double *matrix) {
   if (nprocs == 0) {return;}
   unsigned int *count = (unsigned int*) malloc(nprocs*nprocs*sizeof(unsigned int));
   double tmin = get_tmin_stacktimeline_draw();
   double tmax = get_tmax_stacktimeline_draw();

   bool show_send = comm_matrix_direction_send_checked();
   bool show_recv = comm_matrix_direction_recv_checked();

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
               double size = message.count * message.typeSize / 1024.0 / 1024.0;
               matrix[idx] += size;
               count[idx]++;
            }
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
   double maxsize = matrix[0];
   for (int iproc=1; iproc<nprocs*nprocs; iproc++) {
      maxsize = maxsize > matrix[iproc] ?
         maxsize : matrix[iproc];
   }
   if (maxsize > 0.0) {
      for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
         matrix[iproc] /= maxsize;
      }
   } else {
      maxsize = 1.0;
   }

   free(count);
   count = NULL;

   // update the legend labels
   set_comm_matrix_label_max_value(maxsize);
   set_comm_matrix_label_mid_value(0.5*maxsize);
   set_comm_matrix_label_min_value(0.0);
}
void comm_matrix_update_size_min(int nprocs, double *matrix) {
   if (nprocs == 0) {return;}
   double tmin = get_tmin_stacktimeline_draw();
   double tmax = get_tmax_stacktimeline_draw();

   bool show_send = comm_matrix_direction_send_checked();
   bool show_recv = comm_matrix_direction_recv_checked();

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
               double size = message.count * message.typeSize / 1024.0 / 1024.0;
               if (matrix[idx] < 0.0) {
                  matrix[idx] = size;
               } else {
                  matrix[idx] = 
                     matrix[idx] < size ?
                        matrix[idx] :
                        size;
               }
            }
         }
      }

      // go to the next vfd trace
      vfdtrace = vfdtrace->next;
   }

   // normalize the matrix
   // search for maximum bandwidth
   double maxsize = matrix[0];
   for (int iproc=1; iproc<nprocs*nprocs; iproc++) {
      maxsize = maxsize > matrix[iproc] ?
         maxsize : matrix[iproc];
   }
   if (maxsize > 0.0) {
      for (int iproc=0; iproc<nprocs*nprocs; iproc++) {
         if (matrix[iproc] < 0.0) {
            matrix[iproc] = 0.0;
         } else {
            matrix[iproc] /= maxsize;
         }
      }
   } else {
      maxsize = 1.0;
   }

   // update the legend labels
   set_comm_matrix_label_max_value(maxsize);
   set_comm_matrix_label_mid_value(0.5*maxsize);
   set_comm_matrix_label_min_value(0.0);
}
