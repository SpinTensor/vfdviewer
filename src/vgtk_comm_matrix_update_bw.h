#ifndef VGTK_COMM_MATRIX_UPDATE_BW_H
#define VGTK_COMM_MATRIX_UPDATE_BW_H

void comm_matrix_update_bw_max(int nprocs, double *matrix, double *inorm);
void comm_matrix_update_bw_avg(int nprocs, double *matrix, double *inorm);
void comm_matrix_update_bw_min(int nprocs, double *matrix, double *inorm);

#endif
