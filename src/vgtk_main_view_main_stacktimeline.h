#ifndef VGTK_MAIN_VIEW_MAIN_STACKTIMELINE_H
#define VGTK_MAIN_VIEW_MAIN_STACKTIMELINE_H

#include <gtk/gtk.h>

#include "vfd_types.h"

extern GtkScrolledWindow *main_view_main_stacktimeline_scrolledwindow;
extern GtkBox *main_view_main_stacktimeline_timelineinfo_box;
extern GtkBox *main_view_main_stacktimeline_timeline_box;


void vgtk_build_main_view_main_stacktimeline(GtkBuilder *builder);

#endif
