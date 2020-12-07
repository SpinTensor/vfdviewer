#ifndef VGTK_SURFACES_H
#define VGTK_SURFACES_H

#include <gtk/gtk.h>

#include "vgtk_draw_types.h"

void clear_surface(cairo_surface_t *surface, vgtk_color_t color);

cairo_surface_t *new_vgtk_surface(GtkDrawingArea *drawArea);

void free_surface(cairo_surface_t **surface_ptr);

void reset_surface(GtkDrawingArea *drawArea, cairo_surface_t **surface_ptr);

#endif
