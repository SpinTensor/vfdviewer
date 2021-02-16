#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_hwc_plot.h"

GtkEntry *hwc_plot_derived_counters_formula_entry = NULL;
GtkEntry *hwc_plot_derived_counters_observablename_entry = NULL;

void vgtk_build_hwc_select_observables(GtkBuilder *builder) {
   hwc_plot_derived_counters_formula_entry = GTK_ENTRY(
      gtk_builder_get_object(builder, "hwc_plot_derived_counters_formula_entry"));
   hwc_plot_derived_counters_observablename_entry = GTK_ENTRY(
      gtk_builder_get_object(builder, "hwc_plot_derived_counters_observablename_entry"));

   gtk_builder_connect_signals(builder, NULL);
}

const char *vgtk_hwc_plot_derived_counters_formula_entry_get_text() {
   return gtk_entry_get_text(hwc_plot_derived_counters_formula_entry);
}

const char *vgtk_hwc_plot_derived_counters_observablename_entry_get_text() {
   return gtk_entry_get_text(hwc_plot_derived_counters_observablename_entry);
}

// callback functions
void on_hwc_plot_derived_counters_formula_entry_activate(
   GtkEntry *entry,
   gpointer user_data) {
   (void) entry;
   (void) user_data;

   vgtk_hwc_plot_update();

}
void on_hwc_plot_derived_counters_observablename_entry_activate(
   GtkEntry *entry,
   gpointer  user_data) {
   (void) user_data;

   const char *text = gtk_entry_get_text(entry);
   vgtk_hwc_set_plot_yaxis_title(text);
}
