#include <stdio.h>
#include <stdbool.h>

#include <gtk/gtk.h>

#include "vgtk_stacktimeline_entry.h"

GtkLabel *stacktimeline_cursor_pos_label = NULL;

void vgtk_build_main_stacktimeline_cursorpos_labels(GtkBuilder *builder) {
   stacktimeline_cursor_pos_label = GTK_LABEL(
      gtk_builder_get_object(builder, "stacktimeline_cursor_pos_label"));

   gtk_builder_connect_signals(builder, NULL);
}

void set_stacktimeline_cursorpos_label(double time, int level) {
   // a static string to hold a temporary version of a label
   static char *labelstring = NULL;

   int tmplvl = level;
   int level_digits = 1;
   while (tmplvl > 9) {
      level_digits ++;
      tmplvl /= 10;
   }

   int labelstrlen = 0;
   // 2 chars for "t="
   labelstrlen += 2;
   // 10  from float
   labelstrlen += 10;
   // 1 char for the unit "s"
   labelstrlen += 1;
   // 1 char for the linebreak 
   labelstrlen += 1;
   // 2 chars for "l="
   labelstrlen += 2;
   // chars for level-int
   labelstrlen += level_digits;
   // 1 char for null terminator
   labelstrlen += 1;

   // reallocate stringbuffer if required
   if (labelstring == NULL) {
      labelstring = (char*) malloc(labelstrlen*sizeof(char));
   } else {
      if ((size_t) labelstrlen > strlen(labelstring)) {
         free(labelstring);
         labelstring = (char*) malloc(labelstrlen*sizeof(char));
      }
   }

   snprintf(labelstring,
            labelstrlen-1,
            "t=%4.3les\nl=%*d",
            time,
            level_digits,
            level);

   gtk_label_set_text(stacktimeline_cursor_pos_label, labelstring);
}
