#ifndef VGTK_COMM_MATRIX_GRID_H
#define VGTK_COMM_MATRIX_GRID_H

#include <gtk/gtk.h>

void vgtk_build_comm_matrix_grid(GtkBuilder *builder);

void vgtk_comm_matrix_set_proc_labels(int nprocs);

#endif
