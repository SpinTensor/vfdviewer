#include <stdio.h>
#include <stdbool.h>

#include <gtk/gtk.h>

#include "vgtk_types.h"
#include "vgtk_comm_matrix_mode_switcher.h"

GtkLabel *comm_matrix_cursorpos_label = NULL;

void vgtk_build_comm_matrix_cursorpos_labels(GtkBuilder *builder) {
   comm_matrix_cursorpos_label = GTK_LABEL(
      gtk_builder_get_object(builder, "comm_matrix_cursorpos_label"));

   gtk_builder_connect_signals(builder, NULL);
}

void set_comm_matrix_cursorpos_label(int send_rank, int recv_rank, double value, bool valid) {
   // a static string to hold a temporary version of a label
   static char *labelstring = NULL;

   int tmprank;
   // count send_rank digits
   tmprank = send_rank;
   int send_rank_digits = 1;
   while (tmprank > 9) {
      send_rank_digits ++;
      tmprank /= 10;
   }
   // count recv_rank digits
   tmprank = recv_rank;
   int recv_rank_digits = 1;
   while (tmprank > 9) {
      recv_rank_digits ++;
      tmprank /= 10;
   }

   // get the observable name
   char *obs_string = NULL;
   char *unit_string = NULL;
   switch (comm_matrix_get_unit()) {
      case cm_bw:
         obs_string = "BW=";
         unit_string = "MiB/s";
         break;
      case cm_size:
         obs_string = "size=";
         unit_string = "MiB";
         break;
      case cm_count:
         obs_string = "count=";
         unit_string = "";
         break;
      case cm_time:
         obs_string = "time=";
         unit_string = "s";
         break;
      default:
         obs_string = "";
         unit_string = "";
         break;
   }

   int labelstrlen = 0;
   // 10 chars for "send proc="
   labelstrlen += 10;
   // chars for send_rank_digits
   labelstrlen += send_rank_digits;
   // 1 char for the linebreak 
   labelstrlen += 1;

   // 10 chars for "recv proc="
   labelstrlen += 10;
   // chars for recv_rank_digits
   labelstrlen += recv_rank_digits;
   // 1 char for the linebreak 
   labelstrlen += 1;

   // chars for observable name
   labelstrlen += strlen(obs_string);
   // 10  from float value
   labelstrlen += 10;
   // chars from unit string
   labelstrlen += strlen(unit_string);
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

   if (valid) {
      snprintf(labelstring,
               labelstrlen-1,
               "send proc=%*d\n"
               "recv proc=%*d\n"
               "%s%4.3le%s",
               send_rank_digits, send_rank,
               recv_rank_digits, recv_rank,
               obs_string, value, unit_string);
   } else {
      snprintf(labelstring,
               labelstrlen-1,
               "send proc=%*d\n"
               "recv proc=%*d\n"
               "%s ---",
               send_rank_digits, send_rank,
               recv_rank_digits, recv_rank,
               obs_string);
   }

   gtk_label_set_text(comm_matrix_cursorpos_label, labelstring);
}
