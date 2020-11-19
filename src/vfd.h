#ifndef VFD_H
#define VFD_H

#include "vfd_types.h"

vfd_t *new_vfd(char *filename);

void free_vfd(vfd_t **vfd_ptr);

#endif
