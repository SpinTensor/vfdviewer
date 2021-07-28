#include <gtk/gtk.h>

#include "vfd_types.h"
#include "vgtk_types.h"
#include "vfd_list.h"
#include "vgtk_stacktimeline_hscrollbar.h"
#include "vgtk_stacktimeline_entry.h"
#include "vgtk_comm_matrix.h"

GtkSpinButton *main_stacktimeline_xzoom_spinner = NULL;
GtkSpinButton *main_stacktimeline_yzoom_spinner = NULL;
double main_stacktimeline_xzoom_spinner_value = 1;
double main_stacktimeline_yzoom_spinner_value = 1;

void vgtk_build_main_stacktimeline_spinner(GtkBuilder *builder) {
   main_stacktimeline_xzoom_spinner = GTK_SPIN_BUTTON(
      gtk_builder_get_object(builder, "main_stacktimeline_xzoom_spinner"));
   main_stacktimeline_yzoom_spinner = GTK_SPIN_BUTTON(
      gtk_builder_get_object(builder, "main_stacktimeline_yzoom_spinner"));

   main_stacktimeline_xzoom_spinner_value =
      gtk_spin_button_get_value(main_stacktimeline_xzoom_spinner);
   main_stacktimeline_yzoom_spinner_value =
      gtk_spin_button_get_value(main_stacktimeline_yzoom_spinner);

   gtk_builder_connect_signals(builder, NULL);
}

double stacktimeline_xzoom_spinner_get_value() {
   return main_stacktimeline_xzoom_spinner_value;
}

double stacktimeline_yzoom_spinner_get_value() {
   return main_stacktimeline_yzoom_spinner_value;
}

// callback functions
// if the x-zoom spinner value is changed
void on_main_stacktimeline_xzoom_spinner_value_changed(
   GtkSpinButton *spinbutton, gpointer userdata) {
   (void) spinbutton;
   (void) userdata;

   // update the spinner value
   main_stacktimeline_xzoom_spinner_value =
      gtk_spin_button_get_value(main_stacktimeline_xzoom_spinner);

   double tmin_abs = 0.0;
   double tmax_abs = vfds_max_runtime();

   double iscale = 1.0/main_stacktimeline_xzoom_spinner_value;
   // update the drawing border of the timeaxis
   double tmin = get_tmin_stacktimeline_draw();
   double tmax = get_tmax_stacktimeline_draw();
   double tcen = 0.5*(tmin + tmax);
   double ntmin = tcen - 0.5*iscale*tmax_abs;
   double ntmax = tcen + 0.5*iscale*tmax_abs;

   // correct for border collisions
   if (ntmin < tmin_abs) {
      double diff = tmin_abs - ntmin;
      ntmin = tmin_abs;
      ntmax += diff;
   } else if (ntmax > tmax_abs) {
      double diff = ntmax - tmax_abs;
      ntmax = tmax_abs;
      ntmin -= diff;
   }

   set_tmin_stacktimeline_draw(ntmin);
   set_tmax_stacktimeline_draw(ntmax);

   vgtk_redraw_all_stacktimelines();

   vgtk_adjust_main_stacktimeline_hscrollbar();

   comm_matrix_redraw();
}

// if the y-zoom spinner value is changed
void on_main_stacktimeline_yzoom_spinner_value_changed(
   GtkSpinButton *spinbutton, gpointer userdata) {
   (void) spinbutton;
   (void) userdata;

   // update the spinner value
   main_stacktimeline_yzoom_spinner_value =
      gtk_spin_button_get_value(main_stacktimeline_yzoom_spinner);

   vfd_t *vfdtrace = first_vfd();
   while (vfdtrace != NULL) {
      GtkDrawingArea *drawing_area =
         vfdtrace->vgtk_handles->stackTimelineEntry->drawing_area;
      vgtk_set_drawing_area_size(drawing_area);
      vfdtrace = vfdtrace->next;
   }
}

void stacktimeline_xzoom_spinner_set_value(double value) {
   gtk_spin_button_set_value(main_stacktimeline_xzoom_spinner, value);
}

