#ifndef VGTK_HWC_PLOT_SELECT_OBSERVABLES_H
#define VGTK_HWC_PLOT_SELECT_OBSERVABLES_H

#include <gtk/gtk.h>

void vgtk_build_hwc_select_observables(GtkBuilder *builder);

const char *vgtk_hwc_plot_derived_counters_formula_entry_get_text();

const char *vgtk_hwc_plot_derived_counters_observablename_entry_get_text();

#endif
