#include <gtk/gtk.h>

#include "vgtk_about_dialog.h"

GtkAboutDialog *vgtk_about_dialog = NULL;

void vgtk_build_about_dialog(GtkBuilder *builder) {
   vgtk_about_dialog = GTK_ABOUT_DIALOG(
      gtk_builder_get_object(builder, "about_dialog"));
   gtk_builder_connect_signals(builder, NULL);
}

void vgtk_show_about_dialog() {
   gtk_widget_show(GTK_WIDGET(vgtk_about_dialog));
}

void vgtk_hide_about_dialog() {
   gtk_widget_hide(GTK_WIDGET(vgtk_about_dialog));
}

gint vgtk_run_about_dialog() {
   return gtk_dialog_run(GTK_DIALOG(vgtk_about_dialog));
}

// Callback function for closing the about dialog
void on_about_dialog_response(GtkDialog *dialog, gint response_id) {
   (void) dialog;
   (void) response_id;
   vgtk_hide_about_dialog();
}
