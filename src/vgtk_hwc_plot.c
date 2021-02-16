#include <stdlib.h>

#include <gtk/gtk.h>
#include <slope.h>
//#include <xyscale.h>

#include "vfd_types.h"
#include "vgtk_types.h"
#include "vgtk_hwc_plot.h"
#include "vgtk_hwc_plot_entry.h"
#include "vgtk_hwc_plot_select_observables.h"
#include "vfd_list.h"

GtkBox *main_hwc_plot_box = NULL;
GtkWidget *hwc_plot_view = NULL;

SlopeFigure *hwc_plot_figure;
SlopeScale *hwc_plot_scale;

void vgtk_build_hwc_plot(GtkBuilder *builder) {
   main_hwc_plot_box = GTK_BOX(
      gtk_builder_get_object(builder, "main_hwc_plot_box"));

   // build the slope plot
   hwc_plot_view = slope_view_new();
   hwc_plot_figure = slope_figure_new();
   gtk_box_pack_start(main_hwc_plot_box,
                      hwc_plot_view,
                      TRUE, TRUE, 0);
   gtk_box_reorder_child(main_hwc_plot_box,
                         hwc_plot_view,
                         0);
   slope_view_set_figure(SLOPE_VIEW(hwc_plot_view),
                         hwc_plot_figure);

   hwc_plot_scale = slope_xyscale_new_axis("runtime / s", "", "");
   slope_figure_add_scale(SLOPE_FIGURE(hwc_plot_figure),
                          hwc_plot_scale);

   gtk_widget_show_all(GTK_WIDGET(main_hwc_plot_box));
   gtk_builder_connect_signals(builder, NULL);
}

void vgtk_hwc_plot_update() {
   vfd_t *vfdtrace = first_vfd();

   const char *observable_expression =
      vgtk_hwc_plot_derived_counters_formula_entry_get_text();

   while (vfdtrace != NULL) {
      evaluate_hwc_expression(vfdtrace, observable_expression);
      vfdtrace = vfdtrace->next;
   }

   slope_view_redraw(SLOPE_VIEW(hwc_plot_view));
}

void vgtk_hwc_plot_add_slopeitem(SlopeItem *item) {
   slope_scale_add_item(hwc_plot_scale, item);

   vgtk_hwc_plot_update();
}

void vgtk_hwc_plot_remove_slopeitem(SlopeItem *item) {
   slope_scale_remove_item(hwc_plot_scale, item);

   vgtk_hwc_plot_update();
}

void vgtk_hwc_set_plot_yaxis_title(const char *title) {

   SlopeItem *axis = slope_xyscale_get_axis(SLOPE_XYSCALE(hwc_plot_scale),
                                            SLOPE_XYSCALE_AXIS_LEFT);

   printf("current yaxis title: %s\n", slope_xyaxis_get_title(SLOPE_XYAXIS(axis)));
   slope_xyaxis_set_title(SLOPE_XYAXIS(axis), title);

   printf("new yaxis title: %s\n", slope_xyaxis_get_title(SLOPE_XYAXIS(axis)));
   slope_view_redraw(SLOPE_VIEW(hwc_plot_view));
}

