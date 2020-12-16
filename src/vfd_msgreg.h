#ifndef VFD_MSGREG_H
#define VFD_MSGREG_H

void construct_vfd_msgregs(vfd_t *vfd);

void free_vfd_msgregs(unsigned int nmsgregs, vfd_msgreg_t *msgregs);

void print_vfd_msgregs(vfd_header_t *header,
                       vfd_msgreg_t *msgregs_send,
                       vfd_msgreg_t *msgregs_recv);
#endif
