#ifndef VFD_SAMPLES_H
#define VFD_SAMPLES_H

#include <stdio.h>

#include "vfd_types.h"

void read_vfd_samples(FILE *vfd_file, vfd_header_t *header,
                      vfd_hwc_header_t *hwc_header,
                      vfd_stack_sample_t **stack_samples_ptr,
                      vfd_message_sample_t **message_samples_ptr,
                      vfd_hwc_sample_t **hwc_samples_ptr);

vfd_stack_sample_t read_vfd_stack_sample(FILE *vfd_file);

vfd_message_sample_t read_vfd_message_sample(FILE *vfd_file);

void free_vfd_stack_samples(unsigned int nstack_samples,
                            vfd_stack_sample_t *stack_samples);
void free_vfd_hwc_samples(unsigned int nstack_samples,
                          int n_hwc_obs, int n_formulae,
                          vfd_hwc_sample_t *hwc_samples);

void free_vfd_message_samples(unsigned int nmessage_samples,
                              vfd_message_sample_t *message_samples);

void print_vfd_stack_samples(vfd_header_t *header, vfd_stack_sample_t *samples);

void print_vfd_message_samples(vfd_header_t *header,
                               vfd_message_sample_t *message_samples);

#endif
