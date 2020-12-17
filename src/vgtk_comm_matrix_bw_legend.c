#include <gtk/gtk.h>

#include "vgtk_surfaces.h"
#include "vgtk_colors.h"

GtkDrawingArea *comm_matrix_bw_legend_drawing_area = NULL;
cairo_surface_t *comm_matrix_bw_legend_drawing_surface = NULL;

GtkLabel *comm_matrix_bw_legend_max_label = NULL;
GtkLabel *comm_matrix_bw_legend_mid_label = NULL;
GtkLabel *comm_matrix_bw_legend_min_label = NULL;

double comm_matrix_bw_label_max_value = 1.0;
double comm_matrix_bw_label_mid_value = 0.5;
double comm_matrix_bw_label_min_value = 0.0;

void vgtk_build_comm_matrix_bw_legend(GtkBuilder *builder) {
   comm_matrix_bw_legend_drawing_area = GTK_DRAWING_AREA(
      gtk_builder_get_object(builder, "comm_matrix_bw_legend_drawing_area"));

   comm_matrix_bw_legend_max_label = GTK_LABEL(
      gtk_builder_get_object(builder, "comm_matrix_bw_legend_max_label"));
   comm_matrix_bw_legend_mid_label = GTK_LABEL(
      gtk_builder_get_object(builder, "comm_matrix_bw_legend_mid_label"));
   comm_matrix_bw_legend_min_label = GTK_LABEL(
      gtk_builder_get_object(builder, "comm_matrix_bw_legend_min_label"));

   gtk_builder_connect_signals(builder, NULL);
}

#define LABEL_CONTENT_LEN 16
void set_comm_matrix_bw_label_max_value(double value) {
   static char labelcontent[LABEL_CONTENT_LEN];

   if (comm_matrix_bw_legend_max_label != NULL) {
      snprintf(labelcontent,
               (size_t) (LABEL_CONTENT_LEN - 1),
               "%4.3les", value);
      gtk_label_set_text(comm_matrix_bw_legend_max_label, labelcontent);
   }
}

void set_comm_matrix_bw_label_mid_value(double value) {
   static char labelcontent[LABEL_CONTENT_LEN];

   if (comm_matrix_bw_legend_mid_label != NULL) {
      snprintf(labelcontent,
               (size_t) (LABEL_CONTENT_LEN - 1),
               "%4.3les", value);
      gtk_label_set_text(comm_matrix_bw_legend_mid_label, labelcontent);
   }
}
void set_comm_matrix_bw_label_min_value(double value) {
   static char labelcontent[LABEL_CONTENT_LEN];

   if (comm_matrix_bw_legend_min_label != NULL) {
      snprintf(labelcontent,
               (size_t) (LABEL_CONTENT_LEN - 1),
               "%4.3les", value);
      gtk_label_set_text(comm_matrix_bw_legend_min_label, labelcontent);
   }
}
#undef LABEL_CONTENT_LEN

void vgtk_draw_comm_matrix_bw_legend(cairo_t *cr) {
   GtkDrawingArea *drawing_area = comm_matrix_bw_legend_drawing_area;

   // get surface dimensions
   int sfwidth = gtk_widget_get_allocated_width(GTK_WIDGET(drawing_area));
   int sfheight = gtk_widget_get_allocated_height(GTK_WIDGET(drawing_area));

   // create gradient patterns
   cairo_pattern_t *color_gradient;
   color_gradient = cairo_pattern_create_linear(0.0, sfheight, 0.0, 0.0);
   // purple
   for (int icol=0; icol<vgtk_color_gradient_steps; icol++) {
      double offset = (double) icol / ((double) (vgtk_color_gradient_steps-1.0));
      vgtk_color_t color = vgtk_color_gradient(offset);
      cairo_pattern_add_color_stop_rgba(color_gradient,
                                        offset,
                                        color.red,
                                        color.green,
                                        color.blue,
                                        color.alpha);
   }
   cairo_set_source(cr, color_gradient);

   // fill the bw legend
   cairo_rectangle(cr,
                   0.0, 0.0,
                   sfwidth, sfheight);
   cairo_fill(cr);

   cairo_pattern_destroy(color_gradient);
}

// Callback functions for the bandwidth legend drawing area
gboolean on_comm_matrix_bw_legend_drawing_area_configure_event(
   GtkWidget *widget,
   GdkEventConfigure *event,
   gpointer data) {

   (void) event;
   (void) data;

   if (comm_matrix_bw_legend_drawing_surface != NULL) {
      cairo_surface_destroy(comm_matrix_bw_legend_drawing_surface);
   }

   comm_matrix_bw_legend_drawing_surface = gdk_window_create_similar_surface(
      gtk_widget_get_window(widget),
      CAIRO_CONTENT_COLOR,
      gtk_widget_get_allocated_width(widget),
      gtk_widget_get_allocated_height(widget));

   return TRUE;
}

gboolean on_comm_matrix_bw_legend_drawing_area_draw(
   GtkWidget *widget,
   cairo_t *cr,
   gpointer data) {

   (void) widget;
   (void) data;

   vgtk_draw_comm_matrix_bw_legend(cr);

   return TRUE;
}
