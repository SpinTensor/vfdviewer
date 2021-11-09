#ifndef VGTK_FONT_CHOOSER_DIALOG_H
#define VGTK_FONT_CHOOSER_DIALOG_H

#include <gtk/gtk.h>

void vgtk_build_font_chooser_dialog(GtkBuilder *builder);

char* vgtk_get_selected_font();

int vgtk_get_selected_font_size();

void run_font_chooser_dialog();

#endif
