#ifndef VGTK_OPEN_FILE_DIALOG_H
#define VGTK_OPEN_FILE_DIALOG_H

#include <gtk/gtk.h>

void vgtk_build_open_file_dialog(GtkBuilder *builder);

void vgtk_show_open_file_dialog();

void vgtk_hide_open_file_dialog();

gint vgtk_run_open_file_dialog();

GSList *vgtk_open_file_dialog_get_filenames();

#endif
