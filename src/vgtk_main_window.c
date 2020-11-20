#include <gtk/gtk.h>

GtkWindow *vgtk_main_window = NULL;

void vgtk_show_main_window() {
   gtk_widget_show(GTK_WIDGET(vgtk_main_window));
}

void vgtk_hide_main_window() {
   gtk_widget_hide(GTK_WIDGET(vgtk_main_window));
}
