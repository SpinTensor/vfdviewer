#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "paths.h"

GtkBuilder *builder;
GtkWidget *window;
GtkWidget *fixed;
GtkWidget *button;
GtkWidget *label;

int main(int argc, char **argv) {
   printf("init");
   char *gladefile = get_gladefile_path(argv[0]);
   printf("gladefile = %s\n", gladefile);

   gtk_init(&argc, &argv);

   builder = gtk_builder_new_from_file(gladefile);
   window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

   fixed = GTK_WIDGET(gtk_builder_get_object(builder, "main_fixed"));
   button = GTK_WIDGET(gtk_builder_get_object(builder, "testbutton"));
   label = GTK_WIDGET(gtk_builder_get_object(builder, "testlabel"));

   gtk_builder_connect_signals(builder, NULL);

   gtk_widget_show(window);
   gtk_main();

   free(gladefile);
   gladefile = NULL;
   return 0;
}

void on_testbutton_clicked(GtkButton *b) {
   gtk_label_set_text(GTK_LABEL(label), (const gchar*) "Hello");
}
