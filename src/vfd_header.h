#ifndef VFD_HEADER_H
#define VFD_HEADER_H

#include <stdio.h>

#include "vfd_types.h"

void read_vfd_header(FILE *vfd_file, vfd_header_t **header_ptr);

void free_vfd_header(vfd_header_t *vfd_header);

void print_vfd_header(vfd_header_t *vfd_header);

#endif
