#ifndef VGTK_TYPES
#define VGTK_TYPES

#include <stdbool.h>

#include <gtk/gtk.h>

typedef struct {
   cairo_surface_t *surface;
   GtkDrawingArea *drawing_area;
} vgtk_stackTimelineEntry_t;

typedef struct {
   vgtk_stackTimelineEntry_t *stackTimelineEntry;
} vgtk_handles_t;

typedef enum {
   cm_max,
   cm_avg,
   cm_min
} comm_matrix_mode_t;

typedef enum {
   cm_bw,
   cm_size,
   cm_count
} comm_matrix_unit_t;

typedef struct {
   int nprocs;
   bool valid;
   double *data;
   bool *entry_valid;
   bool any_entry_valid;
   double maxval;
   double minval;
} vgtk_comm_matrix_t;

#endif
