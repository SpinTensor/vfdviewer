#include <gtk/gtk.h>

#include "vgtk_hwc_plot.h"
#include "vgtk_hwc_plot_test_button.h"
#include "vgtk_hwc_plot_select_observables.h"
#include "vgtk_hwc_plot_trace_list.h"

void vgtk_build_main_hwc_plot(GtkBuilder *builder) {
   vgtk_build_hwc_plot(builder);

   vgtk_build_hwc_plot_test_button(builder);
   //vgtk_build_hwc_plot_range_select(builder);
   vgtk_build_hwc_select_observables(builder);
   vgtk_build_hwc_plot_trace_list(builder);

   gtk_builder_connect_signals(builder, NULL);

   vgtk_hwc_plot_update();
}
