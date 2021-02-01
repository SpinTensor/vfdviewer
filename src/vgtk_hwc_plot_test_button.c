#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_hwc_plot.h"

GtkButton *test_replot_button = NULL;

void vgtk_build_hwc_plot_test_button(GtkBuilder *builder) {
   test_replot_button = GTK_BUTTON(
      gtk_builder_get_object(builder, "test_replot_button"));

   gtk_builder_connect_signals(builder, NULL);
}

void on_test_replot_button_clicked(GtkButton *button) {
   (void) button;
   vgtk_hwc_plot_update();
}
