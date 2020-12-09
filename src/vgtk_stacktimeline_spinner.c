#include <gtk/gtk.h>

#include "vfd_types.h"
#include "vgtk_types.h"
#include "vfd_list.h"
#include "vgtk_stacktimeline_entry.h"

GtkSpinButton *main_view_main_stacktimeline_xzoom_spinner = NULL;
GtkSpinButton *main_view_main_stacktimeline_yzoom_spinner = NULL;

void vgtk_build_main_stacktimeline_spinner(GtkBuilder *builder) {
   main_view_main_stacktimeline_xzoom_spinner = GTK_SPIN_BUTTON(
      gtk_builder_get_object(builder, "main_view_main_stacktimeline_xzoom_spinner"));
   main_view_main_stacktimeline_yzoom_spinner = GTK_SPIN_BUTTON(
      gtk_builder_get_object(builder, "main_view_main_stacktimeline_yzoom_spinner"));

   gtk_builder_connect_signals(builder, NULL);
}

double stacktimeline_xzoom_spinner_get_value() {
   return gtk_spin_button_get_value(main_view_main_stacktimeline_xzoom_spinner);
}

double stacktimeline_yzoom_spinner_get_value() {
   return gtk_spin_button_get_value(main_view_main_stacktimeline_yzoom_spinner);
}

// callback functions
// if the x-zoom spinner value is changed
void on_main_view_main_stacktimeline_xzoom_spinner_value_changed(
   GtkSpinButton *spinbutton, gpointer userdata) {
   (void) spinbutton;
   (void) userdata;
}

// if the y-zoom spinner value is changed
void on_main_view_main_stacktimeline_yzoom_spinner_value_changed(
   GtkSpinButton *spinbutton, gpointer userdata) {
   (void) spinbutton;
   (void) userdata;

   vfd_t *vfdtrace = first_vfd();
   while (vfdtrace != NULL) {
      GtkDrawingArea *drawing_area =
         vfdtrace->vgtk_handles->stackTimelineEntry->drawing_area;
      vgtk_set_drawing_area_size(drawing_area);
      vfdtrace = vfdtrace->next;
   }
}

