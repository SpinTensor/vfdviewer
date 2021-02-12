#include <stdio.h>

#include <gtk/gtk.h>

#include "vfd_types.h"

GtkBox *hwc_plot_available_traces_list_box = NULL;

void vgtk_build_hwc_plot_trace_list(GtkBuilder *builder) {
   hwc_plot_available_traces_list_box = GTK_BOX(
      gtk_builder_get_object(builder, "hwc_plot_available_traces_list_box"));

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
