#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_hwc_plot.h"

GtkEntry *hwc_plot_xrange_min_entry = NULL;
GtkEntry *hwc_plot_xrange_max_entry = NULL;
GtkEntry *hwc_plot_yrange_min_entry = NULL;
GtkEntry *hwc_plot_yrange_max_entry = NULL;

void vgtk_build_hwc_plot_range_select(GtkBuilder *builder) {
   hwc_plot_xrange_min_entry = GTK_ENTRY(
      gtk_builder_get_object(builder, "hwc_plot_xrange_min_entry"));
   hwc_plot_xrange_max_entry = GTK_ENTRY(
      gtk_builder_get_object(builder, "hwc_plot_xrange_max_entry"));
   hwc_plot_yrange_min_entry = GTK_ENTRY(
      gtk_builder_get_object(builder, "hwc_plot_yrange_min_entry"));
   hwc_plot_yrange_max_entry = GTK_ENTRY(
      gtk_builder_get_object(builder, "hwc_plot_yrange_max_entry"));

   gtk_builder_connect_signals(builder, NULL);
}

void on_hwc_plot_xrange_min_entry_activate(GtkEntry *entry, gpointer  user_data) {
   (void) user_data;

   const gchar *entered_text = gtk_entry_get_text(entry);
   printf("xrange min str = %s\n", entered_text);

   double value;
   char tmpchar;
   int ret = sscanf(entered_text, "%lf %c", &value, &tmpchar);
   if (ret == 1) {
      printf("xrange min val = %le\n", value);
   } else {
      printf("xrange min val = error\n");
   }
}

void on_hwc_plot_xrange_max_entry_activate(GtkEntry *entry, gpointer  user_data) {
   (void) user_data;

   const gchar *entered_text = gtk_entry_get_text(entry);
   printf("xrange max str = %s\n", entered_text);
}

void on_hwc_plot_yrange_min_entry_activate(GtkEntry *entry, gpointer  user_data) {
   (void) user_data;

   const gchar *entered_text = gtk_entry_get_text(entry);
   printf("xrange min str = %s\n", entered_text);
}

void on_hwc_plot_yrange_max_entry_activate(GtkEntry *entry, gpointer  user_data) {
   (void) user_data;

   const gchar *entered_text = gtk_entry_get_text(entry);
   printf("yrange max str = %s\n", entered_text);
}
