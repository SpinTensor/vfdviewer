#ifndef VGTK_COMM_MATRIX_LEGEND_H
#define VGTK_COMM_MATRIX_LEGEND_H

#include "vgtk_types.h"

void vgtk_build_comm_matrix_legend(GtkBuilder *builder);

void set_comm_matrix_label_max_value(double value);
void set_comm_matrix_label_mid_value(double value);
void set_comm_matrix_label_min_value(double value);

void set_comm_matrix_unit_label(comm_matrix_unit_t unit);

#endif
