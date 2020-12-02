#include <gtk/gtk.h>

#include "vgtk_main_view_gtkstack.h"

void vgtk_build_main_view(GtkBuilder *builder) {
   vgtk_build_main_view_gtkstack(builder);
   gtk_builder_connect_signals(builder, NULL);
}
