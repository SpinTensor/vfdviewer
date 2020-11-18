#include <stdio.h>

#include "vfd_types.h"
#include "vfd_header_IO.h"
#include "vfd_stacks_IO.h"
#include "vfd_samples_IO.h"

vfd_t read_vfd_file(FILE *vfd_file) {
   vfd_t vfd;
   vfd.header = read_vfd_header(vfd_file);
#ifdef _DEBUG
   print_vfd_header(vfd.header);
#endif
   vfd.stacks = read_vfd_stacks(vfd_file, vfd.header);
#ifdef _DEBUG
   print_vfd_stacks(vfd.stacks, vfd.header);
#endif

   read_vfd_samples(vfd_file, vfd.header, &(vfd.stack_samples), &(vfd.messages));

   return vfd;
}
