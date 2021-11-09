#ifndef VFD_SORT_H
#define VFD_SORT_H

#include "vfd_types.h"

void shellsort_message_samples(unsigned int nmsg,
                               vfd_message_sample_t *message_samples);

void shellsort_fcalls(unsigned int nfcalls, vfd_fcall_t *fcalls);

#endif
