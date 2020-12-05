#ifndef VGTK_TYPES
#define VGTK_TYPES

#include <gtk/gtk.h>

typedef struct {
   cairo_surface_t *surface;
   GtkDrawingArea *drawing_area;
} vgtk_stackTimelineEntry_t;

typedef struct {
   vgtk_stackTimelineEntry_t *stackTimelineEntry;
} vgtk_handles_t;

#endif
