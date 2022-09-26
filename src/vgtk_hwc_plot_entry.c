#include <stdlib.h>

#include <gtk/gtk.h>
#include <slope.h>
#include <tinyexpr.h>

#include "vfd_types.h"
#include "vgtk_types.h"
#include "vgtk_hwc_plot.h"
#include "vfd_list.h"
#include "vgtk_hwc_plot_trace_list.h"

// callback definitions
void vgtk_hwc_plot_available_traces_check_button_toggled(
   GtkCheckButton *checkButton,
   gpointer user_data);

vgtk_hwcPlotEntry_t *new_hwcPlotEntry() {
   vgtk_hwcPlotEntry_t *hwcPlotEntry =
      (vgtk_hwcPlotEntry_t*) malloc(sizeof(vgtk_hwcPlotEntry_t));
   hwcPlotEntry->ndata = 0;
   hwcPlotEntry->xcoords = NULL;
   hwcPlotEntry->ycoords = NULL;
   hwcPlotEntry->slopeitem = NULL;
   hwcPlotEntry->showTraceHWCs = NULL;

   return hwcPlotEntry;
}

void init_hwcPlotEntry(vfd_t *vfdtrace) {
   vgtk_hwcPlotEntry_t *entry = vfdtrace->vgtk_handles->hwcPlotEntry;
   // amount of data points is equivalent
   // to the number of function samples
   entry->ndata = vfdtrace->header->function_samplecount;

   // allocate plotting data arrays
   entry->xcoords = (double*) malloc(entry->ndata*sizeof(double));
   entry->ycoords = (double*) malloc(entry->ndata*sizeof(double));
   for (unsigned int i=0; i<entry->ndata; i++ ){
      // convert the sampletime into seconds
      entry->xcoords[i] = vfdtrace->stack_samples[i].sampletime * 1.0e-9;
      entry->ycoords[i] = 0.0;
   }

   // create the slope item to point to the plot data
   char *slopecolors = " rgbmylt";
   int index = vfd_position(vfdtrace);
   char optionstr[3];
   optionstr[0] = slopecolors[(index+1)%strlen(slopecolors)];
   optionstr[1] = '-';
   optionstr[2] = '\0';
   entry->slopeitem =
      slope_xyseries_new_filled(
         vfdtrace->filename,
         entry->xcoords,
         entry->ycoords,
         entry->ndata,
         optionstr);

   vgtk_hwc_plot_add_slopeitem(entry->slopeitem);

   //create the entry in the list for available traces
   entry->showTraceHWCs = GTK_CHECK_BUTTON(
      gtk_check_button_new_with_label(vfdtrace->filename));
   // set default state to toggled (true)
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(entry->showTraceHWCs), TRUE);

   // add checkbutton to hwc-plot trace list
   vgtk_hwc_plot_available_traces_add_trace(entry->showTraceHWCs);

   // connect toggle signal
   g_signal_connect(entry->showTraceHWCs,
                    "toggled",
                    G_CALLBACK(vgtk_hwc_plot_available_traces_check_button_toggled),
                    (gpointer) vfdtrace);
}

void free_hwcPlotEntry(vgtk_hwcPlotEntry_t **hwcPlotEntry_ptr) {
   vgtk_hwcPlotEntry_t *hwcPlotEntry = *hwcPlotEntry_ptr;

   // free data
   free(hwcPlotEntry->xcoords);
   hwcPlotEntry->xcoords = NULL;
   free(hwcPlotEntry->ycoords);
   hwcPlotEntry->ycoords = NULL;

   // remove item from plot
   vgtk_hwc_plot_remove_slopeitem(hwcPlotEntry->slopeitem);

   // remove check button widget from available traces list
   gtk_widget_destroy(GTK_WIDGET(hwcPlotEntry->showTraceHWCs));


}

void evaluate_hwc_expression(vfd_t *vfdtrace, const char *expression) {
   int nhwc = vfdtrace->hwc_header->n_hw_obs;

   double *tmp_var_storage = (double*) malloc((nhwc+1)*sizeof(double));

   te_variable *vars = (te_variable*) malloc((nhwc+1)*sizeof(te_variable));
   for (int ivar=0; ivar<nhwc; ivar++) {
      vars[ivar].name = vfdtrace->hwc_header->te_var_names[ivar];
      vars[ivar].address = tmp_var_storage+ivar;
   }
   // add sampling time as extra variable
   vars[nhwc].name = "t";
   vars[nhwc].address = tmp_var_storage+nhwc;

   int err;
   te_expr *expr = te_compile(expression, vars, nhwc+1, &err);
   vgtk_hwcPlotEntry_t *entry = vfdtrace->vgtk_handles->hwcPlotEntry;
   for (unsigned int i=0; i<entry->ndata; i++) {
      for (int ivar=0; ivar<nhwc; ivar++) {
         tmp_var_storage[ivar] = vfdtrace->hwc_samples->observables[ivar][i];
      }
      tmp_var_storage[nhwc] = entry->xcoords[i];
      entry->ycoords[i] = te_eval(expr);
   }

   te_free(expr);
   free(vars);
   free(tmp_var_storage);
}

void plot_hwc_get_minmax_values(vfd_t *vfdtrace,
                                double *xmin, double *xmax,
                                double *ymin, double *ymax) {
   unsigned int ndata = vfdtrace->vgtk_handles->hwcPlotEntry->ndata;
   double *xcoords = vfdtrace->vgtk_handles->hwcPlotEntry->xcoords;
   double *ycoords = vfdtrace->vgtk_handles->hwcPlotEntry->ycoords;
   *xmin = xcoords[0];
   *xmax = xcoords[0];
   *ymin = ycoords[0];
   *ymax = ycoords[0];

   for (unsigned int i=1; i<ndata; i++) {
      if (xcoords[i] < *xmin) {
         *xmin = xcoords[i];
      } else if (xcoords[i] > *xmax) {
         *xmax = xcoords[i];
      }
      if (ycoords[i] < *ymin) {
         *ymin = ycoords[i];
      } else if (ycoords[i] > *ymax) {
         *ymax = ycoords[i];
      }
   }

   return;
}


// callback function for the trace list check button toggle
void vgtk_hwc_plot_available_traces_check_button_toggled(
   GtkCheckButton *checkButton,
   gpointer user_data) {
   vfd_t *vfdtrace = (vfd_t*) user_data;

   gboolean active;
   active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkButton));
   if (active) {
      vgtk_hwc_plot_add_slopeitem(
         vfdtrace->vgtk_handles->hwcPlotEntry->slopeitem); 
   } else {
      vgtk_hwc_plot_remove_slopeitem(
         vfdtrace->vgtk_handles->hwcPlotEntry->slopeitem);
   }
}
