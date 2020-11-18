#ifndef VFD_HEADER_IO_H
#define VFD_HEADER_IO_H

#include <stdio.h>

#include "vfd_types.h"

vfd_header_t read_vfd_header(FILE *vfd_file);

void print_vfd_header(vfd_header_t vfd_header);

#endif
