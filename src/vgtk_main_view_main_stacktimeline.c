#include <gtk/gtk.h>

GtkScrolledWindow *main_view_main_stacktimeline_scrolledwindow = NULL;
GtkBox *main_view_main_stacktimeline_timelineinfo_box = NULL;
GtkBox *main_view_main_stacktimeline_timeline_box = NULL;

void vgtk_build_main_view_main_stacktimeline(GtkBuilder *builder) {

   main_view_main_stacktimeline_scrolledwindow = GTK_SCROLLED_WINDOW(
      gtk_builder_get_object(builder, "main_view_main_stacktimeline_scrolledwindow"));
   main_view_main_stacktimeline_timelineinfo_box = GTK_BOX(
      gtk_builder_get_object(builder, "main_view_main_stacktimeline_timelineinfo_box"));
   main_view_main_stacktimeline_timeline_box = GTK_BOX(
      gtk_builder_get_object(builder, "main_view_main_stacktimeline_timeline_box"));

   gtk_builder_connect_signals(builder, NULL);
}
