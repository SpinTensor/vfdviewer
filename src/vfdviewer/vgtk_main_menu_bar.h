#ifndef VGTK_MAIN_MENU_BAR_H
#define VGTK_MAIN_MENU_BAR_H

#include <gtk/gtk.h>

void vgtk_build_main_menu_bar(GtkBuilder *builder);

// Callback function to be executed if
// File->Open is activated
void on_main_menu_file_menu_open_item_activate(GtkMenuItem *menuitem);

#endif

