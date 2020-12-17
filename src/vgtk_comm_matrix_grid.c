#include <stdlib.h>

#include <gtk/gtk.h>

GtkGrid *main_comm_matrix_grid = NULL;

static int comm_mat_maxlabels = 0;
static int comm_mat_nlabels = 0;
GtkBox *comm_matrix_send_proc_label_box = NULL;
GtkLabel **comm_matrix_send_proc_labels = NULL;
GtkBox *comm_matrix_recv_proc_label_box = NULL;
GtkLabel **comm_matrix_recv_proc_labels = NULL;

void vgtk_build_comm_matrix_grid(GtkBuilder *builder) {
   main_comm_matrix_grid = GTK_GRID(
      gtk_builder_get_object(builder, "main_comm_matrix_grid"));

   comm_matrix_send_proc_label_box = GTK_BOX(
      gtk_builder_get_object(builder, "comm_matrix_send_proc_label_box"));
   comm_matrix_recv_proc_label_box = GTK_BOX(
      gtk_builder_get_object(builder, "comm_matrix_recv_proc_label_box"));

   gtk_builder_connect_signals(builder, NULL);
}

void vgtk_comm_matrix_create_proc_labels(int nlabels) {
   // assume that no one ever is crazy enough to
   // profile something with 10^32 processes
   char labelcontent[32];
   
   //// first check if a reallocation is required
   //if (nlabels 

   // allocate space for the labels
   //comm_matrix_send_proc_labels = (GtkLabel**) malloc(sizeof(GtkLabel*)*nlabels);
   //comm_matrix_recv_proc_labels = (GtkLabel**) malloc(sizeof(GtkLabel*)*nlabels);



}
