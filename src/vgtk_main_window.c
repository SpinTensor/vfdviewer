#include <gtk/gtk.h>

#include "vfd_list.h"

GtkWindow *vgtk_main_window = NULL;

void vgtk_build_main_window(GtkBuilder *builder) {
   vgtk_main_window = GTK_WINDOW(
      gtk_builder_get_object(builder, "main_window"));
   gtk_builder_connect_signals(builder, NULL);
}

void vgtk_show_main_window() {
   gtk_widget_show(GTK_WIDGET(vgtk_main_window));
}

void vgtk_hide_main_window() {
   gtk_widget_hide(GTK_WIDGET(vgtk_main_window));
}

void on_main_window_destroy(GtkWidget window, gpointer user_data) {
   (void) window;
   (void) user_data;
   // remove all remaining vfd traces
   remove_and_free_vfd_list();

   gtk_main_quit();
}
