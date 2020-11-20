#ifndef VGTK_MAIN_MENU_BAR_H
#define VGTK_MAIN_MENU_BAR_H

#include <gtk/gtk.h>

// Connect main menu bar callback signals
void vgtk_connect_main_menu_bar_signals(GtkBuilder *builder);

// Callback function to be executed if
// File->Open is activated
void on_main_menu_file_menu_open_item_activate(GtkMenuItem *menuitem);

#endif

