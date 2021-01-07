#include <gtk/gtk.h>

GtkFontChooserDialog *vgtk_font_chooser_dialog = NULL;

void vgtk_build_font_chooser_dialog(GtkBuilder *builder) {
   vgtk_font_chooser_dialog = GTK_FONT_CHOOSER_DIALOG(
      gtk_builder_get_object(builder, "font_chooser_dialog"));

   gtk_builder_connect_signals(builder, NULL);
}

char *vgtk_get_selected_font() {
   return gtk_font_chooser_get_font(
      GTK_FONT_CHOOSER(
         vgtk_font_chooser_dialog));
}

int vgtk_get_selected_font_size() {
   return gtk_font_chooser_get_font_size(
      GTK_FONT_CHOOSER(
         vgtk_font_chooser_dialog));
}

void run_font_chooser_dialog() {
   // show the file chooser dialog
   gtk_widget_show(GTK_WIDGET(vgtk_font_chooser_dialog));

   // execute font chooser dialog
   gtk_dialog_run(GTK_DIALOG(vgtk_font_chooser_dialog));

   //hide the font chooser dialog
   gtk_widget_hide(GTK_WIDGET(vgtk_font_chooser_dialog));
}
