#ifndef VGTK_STACK_SEARCHENTRY_H
#define VGTK_STACK_SEARCHENTRY_H

#include <gtk/gtk.h>

void vgtk_build_stack_tree_searchentry(GtkBuilder *builder);

// Callback function if content of search entry is changed
void on_stack_tree_searchentry_search_changed(GtkSearchEntry *entry);

#endif
