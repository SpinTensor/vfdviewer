#ifndef VGTK_HWC_PLOT_TRACE_LIST_H
#define VGTK_HWC_PLOT_TRACE_LIST_H

#include <gtk/gtk.h>

#include "vfd_types.h"

void vgtk_build_hwc_plot_trace_list(GtkBuilder *builder);

void vgtk_hwc_plot_available_traces_add_trace(GtkCheckButton *checkButton);

#endif
