#include <gtk/gtk.h>

#include "vfd_types.h"

GtkScrolledWindow *main_view_main_stacktimeline_scrolledwindow = NULL;
GtkBox *main_view_main_stacktimeline_timelineinfo_box = NULL;
GtkBox *main_view_main_stacktimeline_timeline_box = NULL;

GtkLabel *tmin_stacktimeline_draw_label = NULL;
GtkLabel *tcen_stacktimeline_draw_label = NULL;
GtkLabel *tmax_stacktimeline_draw_label = NULL;

void vgtk_build_main_view_main_stacktimeline(GtkBuilder *builder) {

   main_view_main_stacktimeline_scrolledwindow = GTK_SCROLLED_WINDOW(
      gtk_builder_get_object(builder, "main_view_main_stacktimeline_scrolledwindow"));
   main_view_main_stacktimeline_timelineinfo_box = GTK_BOX(
      gtk_builder_get_object(builder, "main_view_main_stacktimeline_timelineinfo_box"));
   main_view_main_stacktimeline_timeline_box = GTK_BOX(
      gtk_builder_get_object(builder, "main_view_main_stacktimeline_timeline_box"));

   tmin_stacktimeline_draw_label = GTK_LABEL(
      gtk_builder_get_object(builder, "tmin_stacktimeline_draw_label"));
   tcen_stacktimeline_draw_label = GTK_LABEL(
      gtk_builder_get_object(builder, "tcen_stacktimeline_draw_label"));
   tmax_stacktimeline_draw_label = GTK_LABEL(
      gtk_builder_get_object(builder, "tmax_stacktimeline_draw_label"));

   gtk_builder_connect_signals(builder, NULL);
}

#define LABEL_CONTENT_LEN 16
void set_tmin_stacktimeline_draw_label(double time) {
   static char labelcontent[LABEL_CONTENT_LEN];
   
   if (tmin_stacktimeline_draw_label != NULL) {
      snprintf(labelcontent,
               (size_t) (LABEL_CONTENT_LEN - 1), 
               "%4.3les", time);
      gtk_label_set_text(tmin_stacktimeline_draw_label, labelcontent);
   }
}

void set_tcen_stacktimeline_draw_label(double time) {
   static char labelcontent[LABEL_CONTENT_LEN];

   if (tcen_stacktimeline_draw_label != NULL) {
      snprintf(labelcontent,
               (size_t) (LABEL_CONTENT_LEN - 1), 
               "%4.3les", time);
      gtk_label_set_text(tcen_stacktimeline_draw_label, labelcontent);
   }
}

void set_tmax_stacktimeline_draw_label(double time) {
   static char labelcontent[LABEL_CONTENT_LEN];

   if (tmax_stacktimeline_draw_label != NULL) {
      snprintf(labelcontent,
               (size_t) (LABEL_CONTENT_LEN - 1), 
               "%4.3les", time);
      gtk_label_set_text(tmax_stacktimeline_draw_label, labelcontent);
   }
}

#undef LABEL_CONTENT_LEN
