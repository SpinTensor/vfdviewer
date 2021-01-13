#include <stdlib.h>

#include <gtk/gtk.h>
#include <slope.h>

GtkBox *main_hwc_plot_box = NULL;
GtkWidget *hwc_plot_view = NULL;

SlopeFigure *hwc_plot_figure;
SlopeScale *hwc_plot_scale;
SlopeItem *hwc_plot_series;

///
const long n = 100;
double *   x, *y;
///
void vgtk_build_hwc_plot(GtkBuilder *builder) {
   main_hwc_plot_box = GTK_BOX(
      gtk_builder_get_object(builder, "main_hwc_plot_box"));

   // build the slope plot
   hwc_plot_view = slope_view_new();
   gtk_box_pack_start(main_hwc_plot_box,
                      hwc_plot_view,
                      TRUE, TRUE, 0);
   gtk_box_reorder_child(main_hwc_plot_box,
                         hwc_plot_view,
                         0);
   hwc_plot_figure = slope_figure_new();
   slope_view_set_figure(SLOPE_VIEW(hwc_plot_view), hwc_plot_figure);

   ///
   x = g_malloc(n * sizeof(double));
   y = g_malloc(n * sizeof(double));
   hwc_plot_scale = slope_xyscale_new();

   for (long k = 0; k < n; ++k) {
      x[k] = g_random_double();
      y[k] = g_random_double();
   }
   slope_figure_add_scale(SLOPE_FIGURE(hwc_plot_figure), hwc_plot_scale);
   hwc_plot_series = slope_xyseries_new_filled("Random Points", x, y, n, "kor");
   slope_scale_add_item(hwc_plot_scale, hwc_plot_series);
   slope_view_redraw(SLOPE_VIEW(hwc_plot_view));
   ///

   gtk_widget_show_all(GTK_WIDGET(main_hwc_plot_box));
   gtk_builder_connect_signals(builder, NULL);
}
