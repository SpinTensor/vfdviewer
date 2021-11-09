#ifndef VGTK_MAIN_STACKTIMELINE_H
#define VGTK_MAIN_STACKTIMELINE_H

#include <gtk/gtk.h>

#include "vfd_types.h"

extern GtkScrolledWindow *main_stacktimeline_scrolledwindow;
extern GtkBox *main_stacktimeline_timelineinfo_box;
extern GtkBox *main_stacktimeline_timeline_box;

void vgtk_build_main_stacktimeline(GtkBuilder *builder);

void set_tmin_stacktimeline_draw_label(double time);
void set_tcen_stacktimeline_draw_label(double time);
void set_tmax_stacktimeline_draw_label(double time);

#endif
