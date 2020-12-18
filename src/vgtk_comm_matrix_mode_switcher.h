#ifndef VGTK_COMM_MATRIX_MODE_SWITCHER_H
#define VGTK_COMM_MATRIX_MODE_SWITCHER_H

#include "vgtk_types.h"

void vgtk_build_comm_matrix_mode_switcher(GtkBuilder *builder);

comm_matrix_mode_t comm_matrix_get_metric_mode();

comm_matrix_unit_t comm_matrix_get_unit();

#endif
