#include <stdio.h>

#include <gtk/gtk.h>

#include "vfd_types.h"
#include "vfd_list.h"

GtkBox *hwc_plot_available_traces_list_box = NULL;
GtkCheckButton *hwc_plot_available_traces_selectall_checkbutton = NULL;

void vgtk_build_hwc_plot_trace_list(GtkBuilder *builder) {
   hwc_plot_available_traces_list_box = GTK_BOX(
      gtk_builder_get_object(builder, "hwc_plot_available_traces_list_box"));
   hwc_plot_available_traces_selectall_checkbutton = GTK_CHECK_BUTTON(
      gtk_builder_get_object(builder, "hwc_plot_available_traces_selectall_checkbutton"));

   gtk_builder_connect_signals(builder, NULL);
}

void vgtk_hwc_plot_available_traces_add_trace(GtkCheckButton *checkButton) {
   gtk_box_pack_start(hwc_plot_available_traces_list_box,
                      GTK_WIDGET(checkButton),
                      FALSE,
                      FALSE,
                      2);
   gtk_widget_show_all(GTK_WIDGET(hwc_plot_available_traces_list_box));
}

// callback functions
void on_hwc_plot_available_traces_selectall_checkbutton_toggled(
   GtkCheckButton *checkbutton, gpointer userdata) {
   (void) checkbutton;
   (void) userdata;

   gboolean allstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(
      hwc_plot_available_traces_selectall_checkbutton));

   vfd_t *vfdtrace = first_vfd();
   while (vfdtrace != NULL) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
         vfdtrace->vgtk_handles->hwcPlotEntry->showTraceHWCs), allstate);
      vfdtrace = vfdtrace->next;
   }
}
