#include <stdlib.h>

#include <gtk/gtk.h>

#include "vfd_list.h"
#include "vgtk_comm_matrix_grid.h"

GtkGrid *main_comm_matrix_grid = NULL;

GtkLabel *comm_matrix_send_minproc_label = NULL;
GtkLabel *comm_matrix_send_maxproc_label = NULL;
GtkLabel *comm_matrix_recv_minproc_label = NULL;
GtkLabel *comm_matrix_recv_maxproc_label = NULL;

void vgtk_build_comm_matrix_grid(GtkBuilder *builder) {
   main_comm_matrix_grid = GTK_GRID(
      gtk_builder_get_object(builder, "main_comm_matrix_grid"));

   comm_matrix_send_minproc_label = GTK_LABEL(
      gtk_builder_get_object(builder, "comm_matrix_send_minproc_label"));
   comm_matrix_send_maxproc_label = GTK_LABEL(
      gtk_builder_get_object(builder, "comm_matrix_send_maxproc_label"));
   comm_matrix_recv_minproc_label = GTK_LABEL(
      gtk_builder_get_object(builder, "comm_matrix_recv_minproc_label"));
   comm_matrix_recv_maxproc_label = GTK_LABEL(
      gtk_builder_get_object(builder, "comm_matrix_recv_maxproc_label"));

   gtk_builder_connect_signals(builder, NULL);
}

void vgtk_comm_matrix_set_proc_labels(int nprocs) {
   #define LABEL_CONTENT_LEN 16
   char labelcontent[LABEL_CONTENT_LEN];

   snprintf(labelcontent,
            (size_t) (LABEL_CONTENT_LEN - 1),
            "p%d", 0);
   gtk_label_set_text(comm_matrix_send_minproc_label, labelcontent);
   gtk_label_set_text(comm_matrix_recv_minproc_label, labelcontent);
   snprintf(labelcontent,
            (size_t) (LABEL_CONTENT_LEN - 1),
            "p%d", nprocs-1);
   gtk_label_set_text(comm_matrix_send_maxproc_label, labelcontent);
   gtk_label_set_text(comm_matrix_recv_maxproc_label, labelcontent);
}
