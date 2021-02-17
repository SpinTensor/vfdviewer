#ifndef VGKT_HWC_PLOT_ENTRY_H
#define VGKT_HWC_PLOT_ENTRY_H

vgtk_hwcPlotEntry_t *new_hwcPlotEntry();

void init_hwcPlotEntry(vfd_t *vfdtrace);

void free_hwcPlotEntry(vgtk_hwcPlotEntry_t **hwcPlotEntry_ptr);

void evaluate_hwc_expression(vfd_t *vfdtrace, const char *expression);

void plot_hwc_get_minmax_values(vfd_t *vfdtrace,
                                double *xmin, double *xmax,
                                double *ymin, double *ymax);

#endif
