#include <stdio.h>

#include "vfd_types.h"
#include "vfd_header_IO.h"
#include "vfd_stacks_IO.h"
#include "vfd_samples_IO.h"

void read_vfd_file(vfd_t *vfd_file) {
   FILE *vfd_handle = fopen(vfd_file->filename, "r");

   vfd_file->header = read_vfd_header(vfd_handle);
#ifdef _DEBUG
   print_vfd_header(vfd_file->header);
#endif
   vfd_file->stacks = read_vfd_stacks(vfd_handle, vfd_file->header);
#ifdef _DEBUG
   print_vfd_stacks(vfd_file->stacks, vfd_file->header);
#endif

   read_vfd_samples(vfd_handle, vfd_file->header, &(vfd_file->stack_samples), &(vfd_file->messages));
}
