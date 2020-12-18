#ifndef VGTK_COMM_MATRIX_UPDATE_SIZE_H
#define VGTK_COMM_MATRIX_UPDATE_SIZE_H

void comm_matrix_update_size_max(int nprocs, double *matrix);
void comm_matrix_update_size_avg(int nprocs, double *matrix);
void comm_matrix_update_size_min(int nprocs, double *matrix);

#endif
