#include <gtk/gtk.h>

#include "vgtk_main_view_main_stacktimeline.h"

GtkStack *main_view_gtkstack = NULL;

GtkStackSwitcher *main_view_gtkstackswitcher = NULL;

void vgtk_build_main_view_gtkstack(GtkBuilder *builder) {
   main_view_gtkstack = GTK_STACK(
      gtk_builder_get_object(builder, "main_view_gtkstack"));
   main_view_gtkstackswitcher = GTK_STACK_SWITCHER(
      gtk_builder_get_object(builder, "main_view_gtkstackswitcher"));

   // build the stacktimeline viewboxes
   vgtk_build_main_view_main_stacktimeline(builder);

   gtk_builder_connect_signals(builder, NULL);
}
