#ifndef VGTK_HWC_PLOT_H
#define VGTK_HWC_PLOT_H

#include <gtk/gtk.h>
#include <slope.h>

void vgtk_build_hwc_plot(GtkBuilder *builder);

void vgtk_hwc_plot_update();

void vgtk_hwc_plot_add_slopeitem(SlopeItem *item);

void vgtk_hwc_plot_remove_slopeitem(SlopeItem *item);

void vgtk_hwc_set_plot_yaxis_title(const char *title);

void vgtk_hwc_set_plot_xaxis_title(const char *title);

void vgtk_hwc_set_plot_yrange(double min, double max);

void vgtk_hwc_set_plot_xrange(double min, double max);

void vgtk_hwc_reset_plot_range();

#endif
