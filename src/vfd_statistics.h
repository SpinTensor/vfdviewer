#ifndef VFD_STATISTICS_H
#define VFD_STATISTICS_H

#include "vfd_types.h"

void vfd_create_stack_statistics(unsigned int fcallscount, vfd_fcall_t *fcalls,
                                 vfd_stack_entry_t *stacks);
#endif
