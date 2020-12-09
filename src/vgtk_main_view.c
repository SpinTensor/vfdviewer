#include <gtk/gtk.h>

#include "vgtk_main_view_gtkstack.h"
#include "vgtk_stacktimeline_spinner.h"

void vgtk_build_main_view(GtkBuilder *builder) {
   vgtk_build_main_view_gtkstack(builder);

   vgtk_build_main_stacktimeline_spinner(builder);

   gtk_builder_connect_signals(builder, NULL);
}
