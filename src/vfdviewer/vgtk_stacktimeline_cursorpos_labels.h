#ifndef VGTK_STACKTIMELINE_CURSORPOS_LABELS_H
#define VGTK_STACKTIMELINE_CURSORPOS_LABELS_H

#include <gtk/gtk.h>

void vgtk_build_main_stacktimeline_cursorpos_labels(GtkBuilder *builder);

void set_stacktimeline_cursorpos_label(double time, int level);

#endif
