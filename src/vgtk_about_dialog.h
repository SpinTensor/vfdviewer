#ifndef VGTK_ABOUT_DIALOG_H
#define VGTK_ABOUT_DIALOG_H

#include <gtk/gtk.h>

extern GtkAboutDialog *vgtk_about_dialog;

void vgtk_connect_about_dialog_signals(GtkBuilder *builder);

void vgtk_show_about_dialog();

void vgtk_hide_about_dialog();

gint vgtk_run_about_dialog();

#endif
