#include <gtk/gtk.h>

#include "vgtk_hwc_plot.h"
#include "vgtk_hwc_plot_toolbar.h"

void vgtk_build_main_hwc_plot(GtkBuilder *builder) {
   vgtk_build_hwc_plot(builder);

   vgtk_build_hwc_plot_toolbar(builder);

   gtk_builder_connect_signals(builder, NULL);
}
