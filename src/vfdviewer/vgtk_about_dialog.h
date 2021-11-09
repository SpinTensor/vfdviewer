#ifndef VGTK_ABOUT_DIALOG_H
#define VGTK_ABOUT_DIALOG_H

#include <gtk/gtk.h>

void vgtk_build_about_dialog(GtkBuilder *builder);

void vgtk_show_about_dialog();

void vgtk_hide_about_dialog();

gint vgtk_run_about_dialog();

#endif
