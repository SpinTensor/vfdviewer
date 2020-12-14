#ifndef VGTK_STACKTIMELINE_CHECKBUTTONS_H
#define VGTK_STACKTIMELINE_CHECKBUTTONS_H

void vgtk_build_main_stacktimeline_checkbuttons(GtkBuilder *builder);

bool stacktimeline_show_mpi_traffic_checkbutton_checked();

void on_stacktimeline_show_mpi_traffic_checkbutton_toggled(
   GtkCheckButton *checkbutton, gpointer userdata);

#endif 
