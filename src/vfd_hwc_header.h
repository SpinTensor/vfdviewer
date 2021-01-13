#ifndef VFD_HWC_HEADER_H
#define VFD_HWC_HEADER_H

#include <stdio.h>

#include "vfd_types.h"

void read_vfd_hwc_header(FILE *vfd_file, vfd_hwc_header_t **hwc_header_ptr);

void free_vfd_hwc_header(vfd_hwc_header_t *vfd_hwc_header);

void print_vfd_hwc_header(vfd_hwc_header_t *vfd_hwc_header);

#endif
