#include <gtk/gtk.h>

#include "vgtk_types.h"
#include "vgtk_comm_matrix.h"
#include "vgtk_comm_matrix_legend.h"

comm_matrix_mode_t comm_matrix_mode = cm_max;
comm_matrix_unit_t comm_matrix_unit = cm_bw;

GtkRadioButton *comm_matrix_metric_select_max = NULL;
GtkRadioButton *comm_matrix_metric_select_avg = NULL;
GtkRadioButton *comm_matrix_metric_select_min = NULL;

GtkRadioButton *comm_matrix_unit_select_bw = NULL;
GtkRadioButton *comm_matrix_unit_select_size = NULL;
GtkRadioButton *comm_matrix_unit_select_count = NULL;

void vgtk_build_comm_matrix_mode_switcher(GtkBuilder *builder) {
   comm_matrix_metric_select_max = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_metric_select_max"));
   comm_matrix_metric_select_avg = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_metric_select_avg"));
   comm_matrix_metric_select_min = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_metric_select_min"));

   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_metric_select_max),
      TRUE);
   comm_matrix_mode = cm_max;
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_metric_select_avg),
      FALSE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_metric_select_min),
      FALSE);

   comm_matrix_unit_select_bw = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_unit_select_bw"));
   comm_matrix_unit_select_size = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_unit_select_size"));
   comm_matrix_unit_select_count = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_unit_select_count"));

   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_unit_select_bw),
      TRUE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_unit_select_size),
      FALSE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_unit_select_count),
      FALSE);

   // only activate one button
   gtk_builder_connect_signals(builder, NULL);
}

comm_matrix_mode_t comm_matrix_get_metric_mode() {
   return comm_matrix_mode;
}

// callback functions for unit switching radio buttons
void on_comm_matrix_unit_select_bw_toggled(
   GtkRadioButton *button,
   gpointer data) {
   (void) data;

   // get radio button state
   gboolean active;
   active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
   if (active) {
      comm_matrix_unit = cm_bw;
      comm_matrix_invalidate();
      comm_matrix_redraw();

      set_comm_matrix_unit_label(cm_bw);
   }
}

void on_comm_matrix_unit_select_size_toggled(
   GtkRadioButton *button,
   gpointer data) {
   (void) data;

   // get radio button state
   gboolean active;
   active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
   if (active) {
      comm_matrix_unit = cm_size;
      comm_matrix_invalidate();
      comm_matrix_redraw();

      set_comm_matrix_unit_label(cm_size);
   }
}

void on_comm_matrix_unit_select_count_toggled(
   GtkRadioButton *button,
   gpointer data) {
   (void) data;

   // get radio button state
   gboolean active;
   active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
   if (active) {
      comm_matrix_unit = cm_count;
      comm_matrix_invalidate();
      comm_matrix_redraw();

      set_comm_matrix_unit_label(cm_count);
   }
}

// callback functions for metric switching radio buttons
void on_comm_matrix_metric_select_max_toggled(
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

void on_comm_matrix_metric_select_avg_toggled(
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

void on_comm_matrix_metric_select_min_toggled(
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
