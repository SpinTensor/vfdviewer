#ifndef VGTK_COMM_MATRIX_CURSORPOS_LABELS_H
#define VGTK_COMM_MATRIX_CURSORPOS_LABELS_H

#include <stdbool.h>

#include <gtk/gtk.h>

void vgtk_build_comm_matrix_cursorpos_labels(GtkBuilder *builder);

void set_comm_matrix_cursorpos_label(int send_rank, int recv_rank, double value, bool valid);

#endif
