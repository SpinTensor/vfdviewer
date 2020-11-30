#ifndef VFD_FCALLS_H
#define VFD_FCALLS_H

#include "vfd_types.h"

void construct_vfd_fcalls(vfd_t *vfd);

void free_vfd_fcalls(unsigned int nfcalls, vfd_fcall_t *fcalls);

void print_vfd_fcalls(vfd_header_t *header, vfd_fcall_t *fcalls);

#endif
