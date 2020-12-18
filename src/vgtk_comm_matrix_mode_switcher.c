#include <gtk/gtk.h>

#include "vgtk_types.h"
#include "vgtk_comm_matrix.h"

comm_matrix_mode_t comm_matrix_mode = cm_max;

GtkRadioButton *comm_matrix_bw_metric_select_maxbw = NULL;
GtkRadioButton *comm_matrix_bw_metric_select_avgbw = NULL;
GtkRadioButton *comm_matrix_bw_metric_select_minbw = NULL;

void vgtk_build_comm_matrix_mode_switcher(GtkBuilder *builder) {
   comm_matrix_bw_metric_select_maxbw = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_bw_metric_select_maxbw"));
   comm_matrix_bw_metric_select_avgbw = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_bw_metric_select_avgbw"));
   comm_matrix_bw_metric_select_minbw = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_bw_metric_select_minbw"));

   // only activate one button
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_bw_metric_select_maxbw),
      TRUE);
   comm_matrix_mode = cm_max;
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_bw_metric_select_avgbw),
      FALSE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_bw_metric_select_minbw),
      FALSE);

   gtk_builder_connect_signals(builder, NULL);
}

comm_matrix_mode_t comm_matrix_get_metric_mode() {
   return comm_matrix_mode;
}

// callback functions for mode switching radio buttons
void on_comm_matrix_bw_metric_select_maxbw_toggled(
   GtkRadioButton *button,
   gpointer data) {
   (void) data;

   // get radio button state
   gboolean active;
   active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
   if (active) {
      comm_matrix_mode = cm_max;
      comm_matrix_invalidate();
      comm_matrix_redraw();
   }
}

void on_comm_matrix_bw_metric_select_avgbw_toggled(
   GtkRadioButton *button,
   gpointer data) {
   (void) data;

   // get radio button state
   gboolean active;
   active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
   if (active) {
      comm_matrix_mode = cm_avg;
      comm_matrix_invalidate();
      comm_matrix_redraw();
   }
}

void on_comm_matrix_bw_metric_select_minbw_toggled(
   GtkRadioButton *button,
   gpointer data) {
   (void) data;

   // get radio button state
   gboolean active;
   active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
   if (active) {
      comm_matrix_mode = cm_min;
      comm_matrix_invalidate();
      comm_matrix_redraw();
   }
}
