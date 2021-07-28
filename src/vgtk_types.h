#ifndef VGTK_TYPES
#define VGTK_TYPES

#include <stdbool.h>

#include <gtk/gtk.h>
#include <slope.h>

typedef struct {
   cairo_surface_t *surface;
   GtkDrawingArea *drawing_area;
   GtkTooltip *tooltip;
   bool buttonactive;
   double buttonpressx, buttonpressy;
   double movex, movey;
} vgtk_stackTimelineEntry_t;

typedef struct {
   unsigned int ndata;
   double *xcoords;
   double *ycoords;
   SlopeItem *slopeitem;
   GtkCheckButton *showTraceHWCs;
} vgtk_hwcPlotEntry_t;

typedef struct {
   vgtk_stackTimelineEntry_t *stackTimelineEntry;
   vgtk_hwcPlotEntry_t *hwcPlotEntry;
} vgtk_handles_t;

typedef enum {
   cm_max,
   cm_avg,
   cm_min
} comm_matrix_mode_t;

typedef enum {
   cm_bw,
   cm_size,
   cm_count,
   cm_time
} comm_matrix_unit_t;

typedef enum {
   cm_lin,
   cm_log,
   cm_inv
} comm_matrix_plot_t;

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
