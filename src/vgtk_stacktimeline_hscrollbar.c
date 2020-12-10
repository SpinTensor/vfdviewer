#include <gtk/gtk.h>

GtkScrollbar *main_stacktimeline_horizontal_scrollbar = NULL;

void vgtk_build_main_stacktimeline_horizontal_scrollbar(GtkBuilder *builder) {
   main_stacktimeline_horizontal_scrollbar = GTK_SCROLLBAR(
      gtk_builder_get_object(builder, "main_stacktimeline_horizontal_scrollbar"));

   gtk_builder_connect_signals(builder, NULL);
}

// callback functions
void on_main_stacktimeline_horizontal_scrollbar_value_changed(
   GtkRange *range, gpointer user_data) {
   (void) range;
   (void) user_data;
}
