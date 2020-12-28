#include <stdbool.h>

#include <gtk/gtk.h>

#include "vgtk_stacktimeline_entry.h"

GtkCheckButton *stacktimeline_show_mpi_send_checkbutton = NULL;
GtkCheckButton *stacktimeline_show_mpi_recv_checkbutton = NULL;

void vgtk_build_main_stacktimeline_checkbuttons(GtkBuilder *builder) {
   stacktimeline_show_mpi_send_checkbutton = GTK_CHECK_BUTTON(
      gtk_builder_get_object(builder, "stacktimeline_show_mpi_send_checkbutton"));
   stacktimeline_show_mpi_recv_checkbutton = GTK_CHECK_BUTTON(
      gtk_builder_get_object(builder, "stacktimeline_show_mpi_recv_checkbutton"));

   // deactivate buttons as default
   gtk_toggle_button_set_active(
      GTK_TOGGLE_BUTTON(
         stacktimeline_show_mpi_send_checkbutton),
      FALSE);
   gtk_toggle_button_set_active(
      GTK_TOGGLE_BUTTON(
         stacktimeline_show_mpi_recv_checkbutton),
      FALSE);

   gtk_builder_connect_signals(builder, NULL);
}

bool stacktimeline_show_mpi_send_checkbutton_checked() {
   return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(
      stacktimeline_show_mpi_send_checkbutton));
}

bool stacktimeline_show_mpi_recv_checkbutton_checked() {
   return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(
      stacktimeline_show_mpi_recv_checkbutton));
}

// callback functions
// if the show mpi traffic check button is clicked
void on_stacktimeline_show_mpi_send_checkbutton_toggled(
   GtkCheckButton *checkbutton, gpointer userdata) {
   (void) checkbutton;
   (void) userdata;

   vgtk_redraw_all_stacktimelines();
}

// if the show mpi traffic check button is clicked
void on_stacktimeline_show_mpi_recv_checkbutton_toggled(
   GtkCheckButton *checkbutton, gpointer userdata) {
   (void) checkbutton;
   (void) userdata;

   vgtk_redraw_all_stacktimelines();
}
