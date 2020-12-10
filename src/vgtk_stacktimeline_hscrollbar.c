#include <gtk/gtk.h>

#include "vfd_list.h"
#include "vgtk_stacktimeline_entry.h"

GtkScrollbar *main_stacktimeline_horizontal_scrollbar = NULL;
GtkAdjustment *main_stacktimeline_horizontal_scrollbar_adjustment = NULL;

void vgtk_build_main_stacktimeline_horizontal_scrollbar(GtkBuilder *builder) {
   main_stacktimeline_horizontal_scrollbar = GTK_SCROLLBAR(
      gtk_builder_get_object(builder, "main_stacktimeline_horizontal_scrollbar"));

   main_stacktimeline_horizontal_scrollbar_adjustment = GTK_ADJUSTMENT(
      gtk_builder_get_object(builder,
         "main_stacktimeline_horizontal_scrollbar_adjustment"));

   gtk_builder_connect_signals(builder, NULL);
}

void vgtk_adjust_main_stacktimeline_hscrollbar() {
   double mintime = 0.0;
   double maxtime = vfds_max_runtime();
   double winmintime = get_tmin_stacktimeline_draw();
   double winmaxtime = get_tmax_stacktimeline_draw();

   GtkAdjustment *adjustment = main_stacktimeline_horizontal_scrollbar_adjustment;

   double new_pagesize = winmaxtime - winmintime;

   gtk_adjustment_configure(adjustment,
                            winmintime,
                            mintime,
                            maxtime,
                            new_pagesize,
                            new_pagesize,
                            new_pagesize);
}

// callback functions
void on_main_stacktimeline_horizontal_scrollbar_value_changed(
   GtkRange *range, gpointer user_data) {
   (void) user_data;

   double new_value = gtk_range_get_value(range);

   double winmintime = get_tmin_stacktimeline_draw();
   double winmaxtime = get_tmax_stacktimeline_draw();
   double deltat = winmaxtime - winmintime;

   // translate the drawn stacktimeline to the new value
   set_tmin_stacktimeline_draw(new_value);
   set_tmax_stacktimeline_draw(new_value+deltat);

   vgtk_redraw_all_stacktimelines();
}
