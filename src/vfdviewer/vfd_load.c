#include "vgtk_stack_treeview.h"
#include "vgtk_stack_list_treeview.h"
#include "vgtk_stacktimeline_entry.h"
#include "vgtk_stacktimeline_spinner.h"
#include "vgtk_hwc_plot_entry.h"
#include "vgtk_hwc_plot_select_observables.h"
#include "vfd_list.h"

void vfd_load_file(char *filename) {
   vfd_t *vfdfile = new_vfd(filename);
   append_vfd(vfdfile);
   // add the vfdtrace to the stack treeView
   vgtk_stack_tree_add_vfdtrace(vfdfile);
   vgtk_stack_list_add_vfdtrace(vfdfile);
   // add the vfdtrace to the timeline view
   init_stacktimeline_entry(vfdfile);
   init_hwcPlotEntry(vfdfile);
   set_hwc_plot_derived_counters_select_counter_comboboxtext_options();

   // reset horizontal zoom to 1
   stacktimeline_xzoom_spinner_set_value(1.0);
   // update the timeline label
   set_tmin_stacktimeline_draw(0.0);
   set_tmax_stacktimeline_draw(vfds_max_runtime());
}
