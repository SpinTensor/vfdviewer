#include <stdbool.h>

#include <gtk/gtk.h>

#include "vgtk_types.h"
#include "vgtk_comm_matrix.h"
#include "vgtk_comm_matrix_legend.h"

comm_matrix_mode_t comm_matrix_mode = cm_max;
comm_matrix_unit_t comm_matrix_unit = cm_bw;
comm_matrix_plot_t comm_matrix_plot = cm_lin;

GtkRadioButton *comm_matrix_metric_select_max = NULL;
GtkRadioButton *comm_matrix_metric_select_avg = NULL;
GtkRadioButton *comm_matrix_metric_select_min = NULL;

GtkRadioButton *comm_matrix_unit_select_bw = NULL;
GtkRadioButton *comm_matrix_unit_select_size = NULL;
GtkRadioButton *comm_matrix_unit_select_count = NULL;
GtkRadioButton *comm_matrix_unit_select_time = NULL;

GtkRadioButton *comm_matrix_plot_select_linear = NULL;
GtkRadioButton *comm_matrix_plot_select_log = NULL;

GtkCheckButton *comm_matrix_direction_select_send = NULL;
GtkCheckButton *comm_matrix_direction_select_recv = NULL;

void vgtk_build_comm_matrix_mode_switcher(GtkBuilder *builder) {
   // Metric selection buttons
   comm_matrix_metric_select_max = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_metric_select_max"));
   comm_matrix_metric_select_avg = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_metric_select_avg"));
   comm_matrix_metric_select_min = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_metric_select_min"));

   // only activate one button
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

   // unit selection buttons
   comm_matrix_unit_select_bw = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_unit_select_bw"));
   comm_matrix_unit_select_size = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_unit_select_size"));
   comm_matrix_unit_select_count = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_unit_select_count"));
   comm_matrix_unit_select_time = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_unit_select_time"));

   // only activate one button
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_unit_select_bw),
      TRUE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_unit_select_size),
      FALSE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_unit_select_count),
      FALSE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_unit_select_time),
      FALSE);

   // plot type selection buttons
   comm_matrix_plot_select_linear = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_plot_select_linear"));
   comm_matrix_plot_select_log = GTK_RADIO_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_plot_select_log"));

   // only activate one button
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_plot_select_linear),
      TRUE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
      comm_matrix_plot_select_log),
      FALSE);

   // direction activation buttons
   comm_matrix_direction_select_send = GTK_CHECK_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_direction_select_send"));
   comm_matrix_direction_select_recv = GTK_CHECK_BUTTON(
      gtk_builder_get_object(builder, "comm_matrix_direction_select_recv"));

   // set default status of direction button to active
   gtk_toggle_button_set_active(
      GTK_TOGGLE_BUTTON(
         comm_matrix_direction_select_send),
      TRUE);
   gtk_toggle_button_set_active(
      GTK_TOGGLE_BUTTON(
         comm_matrix_direction_select_recv),
      TRUE);

   gtk_builder_connect_signals(builder, NULL);
}

comm_matrix_mode_t comm_matrix_get_metric_mode() {
   return comm_matrix_mode;
}

comm_matrix_unit_t comm_matrix_get_unit() {
   return comm_matrix_unit;
}

comm_matrix_plot_t comm_matrix_get_plot() {
   return comm_matrix_plot;
}

bool comm_matrix_direction_send_checked() {
   return gtk_toggle_button_get_active(
      GTK_TOGGLE_BUTTON(
         comm_matrix_direction_select_send));
}

bool comm_matrix_direction_recv_checked() {
   return gtk_toggle_button_get_active(
      GTK_TOGGLE_BUTTON(
         comm_matrix_direction_select_recv));
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

void on_comm_matrix_unit_select_time_toggled(
   GtkRadioButton *button,
   gpointer data) {
   (void) data;

   // get radio button state
   gboolean active;
   active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
   if (active) {
      comm_matrix_unit = cm_time;
      comm_matrix_invalidate();
      comm_matrix_redraw();

      set_comm_matrix_unit_label(cm_time);
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

// callback functions for plot type switching radio buttons
void on_comm_matrix_plot_select_linear_toggled(
   GtkRadioButton *button,
   gpointer data) {
   (void) data;

   // get radio button state
   gboolean active;
   active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
   if (active) {
      comm_matrix_plot = cm_lin;
      comm_matrix_invalidate();
      comm_matrix_redraw();
   }
}

void on_comm_matrix_plot_select_log_toggled(
   GtkRadioButton *button,
   gpointer data) {
   (void) data;

   // get radio button state
   gboolean active;
   active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
   if (active) {
      comm_matrix_plot = cm_log;
      comm_matrix_invalidate();
      comm_matrix_redraw();
   }
}

// callback function for direction selection checkbuttons
void on_comm_matrix_direction_select_send_toggled(
   GtkCheckButton *checkbutton,
   gpointer userdata) {
   (void) checkbutton;
   (void) userdata;

   comm_matrix_invalidate();
   comm_matrix_redraw();
}

void on_comm_matrix_direction_select_recv_toggled(
   GtkCheckButton *checkbutton,
   gpointer userdata) {
   (void) checkbutton;
   (void) userdata;

   comm_matrix_invalidate();
   comm_matrix_redraw();
}
