#include <stdio.h>

#include <gtk/gtk.h>

#include "vgtk_open_file_dialog.h"
#include "vgtk_about_dialog.h"
#include "vgtk_main_menu_bar.h"
#include "vgtk_stack_treeview.h"
#include "vfd_list.h"

void vgtk_build_main_menu_bar(GtkBuilder *builder) {
   gtk_builder_connect_signals(builder, NULL);
}

// Callback function to be executed if
// File->Open is activated
void on_main_menu_file_menu_open_item_activate(GtkMenuItem *menuitem) {
   (void) menuitem;
   run_open_file_dialog();
}

// // Callback function to be executed if
// Help->About is activated
void on_main_menu_help_menu_about_activate(GtkMenuItem *menuitem) {
   (void) menuitem;
   vgtk_show_about_dialog();
}
