#ifndef VGTK_HWC_PLOT_H
#define VGTK_HWC_PLOT_H

#include <gtk/gtk.h>
#include <slope.h>

void vgtk_build_hwc_plot(GtkBuilder *builder);

void vgtk_hwc_plot_update();

void vgtk_hwc_plot_add_slopeitem(SlopeItem *item);

#endif