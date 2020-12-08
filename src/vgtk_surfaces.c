#include <stdlib.h>

#include <gtk/gtk.h>

#include "vgtk_colors.h"

void clear_surface(cairo_surface_t *surface) {
   cairo_t *cr;
   cr = cairo_create(surface);

   cairo_set_source_rgba(cr,
                         1.0,
                         1.0,
                         1.0,
                         1.0);

   cairo_paint(cr);

   cairo_destroy(cr);
}

cairo_surface_t *new_vgtk_surface(GtkDrawingArea *drawArea) {
   cairo_surface_t *surface;

   GtkWidget *tmpwidget = GTK_WIDGET(drawArea);

   surface = gdk_window_create_similar_surface(
      gtk_widget_get_window(tmpwidget),
      CAIRO_CONTENT_COLOR,
      gtk_widget_get_allocated_width(tmpwidget),
      gtk_widget_get_allocated_height(tmpwidget));

   clear_surface(surface);

   return surface;
}

void free_surface(cairo_surface_t **surface_ptr) {
   cairo_surface_t *surface = *surface_ptr;

   if (surface != NULL) {
      cairo_surface_destroy (surface);
   }
   surface = NULL;
}

void reset_surface(GtkDrawingArea *drawArea, cairo_surface_t **surface_ptr) {
   free_surface(surface_ptr);

   *surface_ptr = new_vgtk_surface(drawArea);
}
