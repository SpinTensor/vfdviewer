#include <stdio.h>

#include <gtk/gtk.h>

GtkSearchEntry *stack_tree_searchentry = NULL;

void vgtk_build_stack_tree_searchentry(GtkBuilder *builder) {
   stack_tree_searchentry = GTK_SEARCH_ENTRY(
      gtk_builder_get_object(builder, "stack_tree_searchentry"));

   gtk_builder_connect_signals(builder, NULL);
}

// Callback function if content of search entry is changed
void on_stack_tree_searchentry_search_changed(GtkSearchEntry *entry) {
   printf("%s\n", gtk_entry_get_text(GTK_ENTRY(entry)));
}
