#ifndef VFD_HEADER_IO_H
#define VFD_HEADER_IO_H

#include <stdio.h>

#include "vfd_types.h"

void read_vfd_header(FILE *vfd_file, vfd_header_t **header_ptr);

void print_vfd_header(vfd_header_t *vfd_header);

#endif
