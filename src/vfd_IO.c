#include <stdio.h>

#include "vfd_types.h"
#include "vfd_header_IO.h"

vfd_t read_vfd_file(FILE *vfd_file) {
   vfd_t vfd;
   vfd.header = read_vfd_header(vfd_file);
#ifdef _DEBUG
   print_vfd_header(vfd.header);
#endif
   return vfd;
}

//vfd_stack_entry_t *read_vfd_stacks(FILE *vfd_file, vfd_header_t);
//
//vfd_stack_sample_t read_vfd_stack_sample(FILE *vfd_file);
//
//vfd_message_t read_vfd_message_sample(FILE *vfd_file);
