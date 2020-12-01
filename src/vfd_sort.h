#ifndef VFD_SORT_H
#define VFD_SORT_H

#include "vfd_types.h"

void shellsort_messages(unsigned int nmsg, vfd_message_t *messages);

void shellsort_fcalls(unsigned int nfcalls, vfd_fcall_t *fcalls);

#endif
