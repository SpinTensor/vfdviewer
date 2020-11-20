#include <gtk/gtk.h>

GtkFileChooser *vgtk_open_file_dialog = NULL;

void vgtk_show_open_file_dialog() {
   gtk_widget_show(GTK_WIDGET(vgtk_open_file_dialog));
}

void vgtk_hide_open_file_dialog() {
   gtk_widget_hide(GTK_WIDGET(vgtk_open_file_dialog));
}

gint vgtk_run_open_file_dialog() {
   return gtk_dialog_run(GTK_DIALOG(vgtk_open_file_dialog));
}

GSList *vgtk_open_file_dialog_get_filenames() {
   return gtk_file_chooser_get_filenames(vgtk_open_file_dialog);
}
