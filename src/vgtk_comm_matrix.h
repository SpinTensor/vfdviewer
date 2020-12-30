#ifndef VGTK_COMM_MATRIX_H
#define VGTK_COMM_MATRIX_H

#include <gtk/gtk.h>

void vgtk_build_comm_matrix(GtkBuilder *builder);

double vgtk_comm_matrix_get_maxval();

double vgtk_comm_matrix_get_minval();

void comm_matrix_invalidate();

void comm_matrix_redraw();
#endif
