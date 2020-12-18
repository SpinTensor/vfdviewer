#include <gtk/gtk.h>

#include "vgtk_comm_matrix_bw_legend.h"
#include "vgtk_comm_matrix_grid.h"
#include "vgtk_comm_matrix_mode_switcher.h"
#include "vgtk_comm_matrix.h"

void vgtk_build_main_comm_matrix(GtkBuilder *builder) {
   vgtk_build_comm_matrix_bw_legend(builder);
   vgtk_build_comm_matrix_grid(builder);
   vgtk_build_comm_matrix(builder);
   vgtk_build_comm_matrix_mode_switcher(builder);

   gtk_builder_connect_signals(builder, NULL);
}
