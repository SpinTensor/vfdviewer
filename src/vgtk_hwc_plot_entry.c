#include <stdlib.h>

#include <gtk/gtk.h>
#include <slope.h>

#include "vfd_types.h"
#include "vgtk_types.h"
#include "vgtk_hwc_plot.h"
#include "vfd_list.h"

vgtk_hwcPlotEntry_t *new_hwcPlotEntry() {
   vgtk_hwcPlotEntry_t *hwcPlotEntry =
      (vgtk_hwcPlotEntry_t*) malloc(sizeof(vgtk_hwcPlotEntry_t));
   hwcPlotEntry->ndata = 0;
   hwcPlotEntry->xcoords = NULL;
   hwcPlotEntry->ycoords = NULL;
   hwcPlotEntry->slopeitem = NULL;

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
      entry->xcoords[i] = vfdtrace->stack_samples[i].sampletime * 1.0e-6;
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
}

void free_hwcPlotEntry(vgtk_hwcPlotEntry_t **hwcPlotEntry_ptr) {
   vgtk_hwcPlotEntry_t *hwcPlotEntry = *hwcPlotEntry_ptr;

   // 
   free(hwcPlotEntry->xcoords);
   hwcPlotEntry->xcoords = NULL;
   free(hwcPlotEntry->ycoords);
   hwcPlotEntry->ycoords = NULL;

}
