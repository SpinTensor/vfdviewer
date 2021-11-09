#ifndef VGTK_STACKTIMELINE_ENTRY_H
#define VGTK_STACKTIMELINE_ENTRY_H

#include "vfd_types.h"
#include "vgtk_types.h"

vgtk_stackTimelineEntry_t *new_stackTimelineEntry();

void init_stacktimeline_entry(vfd_t *vfdtrace);

void free_stackTimelineEntry(vgtk_stackTimelineEntry_t **stackTimelineEntry_ptr);

void vgtk_draw_stacktimeline(
   GtkDrawingArea *drawing_area,
   cairo_surface_t *surface,
   vfd_t *vfdtrace);

void vgtk_set_drawing_area_size(GtkDrawingArea *drawing_area);

void vgtk_redraw_all_stacktimelines();

double get_tmin_stacktimeline_draw();
double get_tmax_stacktimeline_draw();
void set_tmin_stacktimeline_draw(double new_time);
void set_tmax_stacktimeline_draw(double new_time);

int get_hmax_stacktimeline_draw();
void set_hmax_stacktimeline_draw(int new_height);

#endif
