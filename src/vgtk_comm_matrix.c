#include <gtk/gtk.h>

#include "vgtk_colors.h"

GtkDrawingArea *comm_matrix_matrix_drawing_area = NULL;
cairo_surface_t *comm_matrix_matrix_drawing_surface = NULL;

void vgtk_build_comm_matrix(GtkBuilder *builder) {
   comm_matrix_matrix_drawing_area = GTK_DRAWING_AREA(
      gtk_builder_get_object(builder, "comm_matrix_matrix_drawing_area"));

   gtk_builder_connect_signals(builder, NULL);
}

void vgtk_draw_comm_matrix(int nprocs, cairo_t *cr) {
   GtkDrawingArea *drawing_area = comm_matrix_matrix_drawing_area;

   // get surface dimensions
   int sfwidth = gtk_widget_get_allocated_width(GTK_WIDGET(drawing_area));
   int sfheight = gtk_widget_get_allocated_height(GTK_WIDGET(drawing_area));

   double rect_width = (double) sfwidth / ((double) nprocs);
   double rect_height = (double) sfheight / ((double) nprocs);

   for (int icol=0; icol<nprocs; icol++) {
      for (int irow=0; irow<nprocs; irow++) {
         double random = (double)rand() / (double)((unsigned)RAND_MAX + 1);
         vgtk_color_t color = vgtk_color_gradient(random);

         cairo_set_source_rgba(cr,
                               color.red,
                               color.green,
                               color.blue,
                               color.alpha);
         cairo_rectangle(cr,
                         icol*rect_width, irow*rect_height,
                         rect_width, rect_height);
         cairo_fill_preserve(cr);

         cairo_set_source_rgba(cr,
                               195.0/255.0,
                               195.0/255.0,
                               195.0/255.0,
                               0.5);
         cairo_stroke(cr);

      }
   }
}

// Callback functions for the communication matrix drawing area
gboolean on_comm_matrix_matrix_drawing_area_configure_event(
   GtkWidget *widget,
   GdkEventConfigure *event,
   gpointer data) {

   (void) event;
   (void) data;

   if (comm_matrix_matrix_drawing_surface != NULL) {
      cairo_surface_destroy(comm_matrix_matrix_drawing_surface);
   }

   comm_matrix_matrix_drawing_surface = gdk_window_create_similar_surface(
      gtk_widget_get_window(widget),
      CAIRO_CONTENT_COLOR,
      gtk_widget_get_allocated_width(widget),
      gtk_widget_get_allocated_height(widget));

   return TRUE;
}

gboolean on_comm_matrix_matrix_drawing_area_draw(
   GtkWidget *widget,
   cairo_t *cr,
   gpointer data) {

   vgtk_draw_comm_matrix(64, cr);

   return TRUE;
}
