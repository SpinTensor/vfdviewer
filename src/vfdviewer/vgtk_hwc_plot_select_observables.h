#ifndef VGTK_HWC_PLOT_SELECT_OBSERVABLES_H
#define VGTK_HWC_PLOT_SELECT_OBSERVABLES_H

#include <gtk/gtk.h>

void vgtk_build_hwc_select_observables(GtkBuilder *builder);

void set_hwc_plot_derived_counters_select_counter_comboboxtext_options();

const char *vgtk_hwc_plot_derived_counters_formula_entry_get_text();

const char *vgtk_hwc_plot_derived_counters_observablename_entry_get_text();

#endif
