#include <stdio.h>
#include <regex.h>

#include <gtk/gtk.h>

#include "vfd_list.h"
#include "vfd_stacks.h"
#include "vgtk_stack_treeview.h"
#ifdef _DEBUG
#include "v_timer.h"
#endif

GtkSearchEntry *stack_tree_searchentry = NULL;

void vgtk_build_stack_tree_searchentry(GtkBuilder *builder) {
   stack_tree_searchentry = GTK_SEARCH_ENTRY(
      gtk_builder_get_object(builder, "stack_tree_searchentry"));

   gtk_builder_connect_signals(builder, NULL);
}

const char *vgtk_stack_tree_searchentry_get_text() {
   return gtk_entry_get_text(GTK_ENTRY(stack_tree_searchentry));
}

void vgtk_stack_tree_searchentry_set_text(const char *text) {
    gtk_entry_set_text(GTK_ENTRY(stack_tree_searchentry), text);
}


// Callback function if content of search entry is changed
void on_stack_tree_searchentry_search_changed(GtkSearchEntry *entry) {
#ifdef _DEBUG
   struct timespec t_start = current_time();
#endif
   (void) entry;
   // update the visibility of the tree with the search entry
   // first get the actual search entry text
   const gchar *search_text = vgtk_stack_tree_searchentry_get_text();

   // compile a regular expression out of this
   regex_t regex;
   if (regcomp(&regex, search_text, 0) != 0) {
      // compilation of regular expression failed
      // no refiltering of the tree
      return;
   }

   // now loop over all vfd traces and
   // determine the visibility for all stack entries
   vfd_t *vfdptr = first_vfd();
   while (vfdptr != NULL) {
      // skip the init function for now
      // as it is not displayed in the treeview
      // and is selfreferential,
      // thus leading to endless recursion
      vfdptr->stacks[1].visible_in_treeview =
         update_stack_visible_in_treeview(&regex, vfdptr->stacks+1);

      // set the visibility of the init function
      // to the same value as the the main function
      vfdptr->stacks[0].visible_in_treeview = vfdptr->stacks[1].visible_in_treeview;

      // go to next vfd trace
      vfdptr = vfdptr->next;
   }
   vgtk_stack_tree_refilter();
   vgtk_stack_tree_expand();
#ifdef _DEBUG
   struct timespec t_end = current_time();
   fprintf(stderr, "\n");
   fprintf(stderr, "Stack tree seach:\n");
   fprintf(stderr, "   matching \"%s\"\n", search_text);
   fprintf(stderr, "   updated in %10.3es\n", timediff(t_start, t_end));
#endif
}
