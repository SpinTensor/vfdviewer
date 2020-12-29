#ifndef VGTK_COMM_MATRIX_MODE_SWITCHER_H
#define VGTK_COMM_MATRIX_MODE_SWITCHER_H

#include <stdbool.h>

#include <gtk/gtk.h>

#include "vgtk_types.h"

void vgtk_build_comm_matrix_mode_switcher(GtkBuilder *builder);

comm_matrix_mode_t comm_matrix_get_metric_mode();

comm_matrix_unit_t comm_matrix_get_unit();

comm_matrix_plot_t comm_matrix_get_plot();

bool comm_matrix_direction_send_checked();

bool comm_matrix_direction_recv_checked();


#endif
