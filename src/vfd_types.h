#ifndef VFD_TYPES_H
#define VFD_TYPES_H

#include <stdbool.h>

#define VFTR_VERSIONSIZE 16
#define DATESTRINGSIZE 24

typedef struct {
   int vfd_version;
   char vftrace_version[VFTR_VERSIONSIZE+1];
   char date[DATESTRINGSIZE+1];
   long long interval;
   int nthreads;
   int mythread;
   int nranks;
   int myrank;
   double runtime;
   unsigned int function_samplecount;
   unsigned int message_samplecount;
   unsigned int stackscount;
   long stacksoffset;
   long sampleoffset;
   int nhwc;
} vfd_header_t;

typedef enum {
   fnct_entry,
   fnct_exit,
   mpi_message
} vfd_sample_kind_enum;

typedef struct vdf_stack_entry_type vfd_stack_entry_t;
struct vdf_stack_entry_type{
   int ID;
   int level;
   int callerID;
   vfd_stack_entry_t *caller;
   int ncallees;
   vfd_stack_entry_t **callees;
   bool precise;
   int namelen;
   char *name;
};

typedef struct {
   vfd_sample_kind_enum kind;
   int stackID;
   long long sampletime;
} vfd_stack_sample_t;

typedef enum {
   send,
   recv
} vfd_message_dir_enum;

typedef struct {
   vfd_message_dir_enum dir;
   int rank;
   int typeID;
   int count;
   int typeSize;
   int tag;
   long long tstart_usec;
   double dtstart_sec;
   long long tend_usec;
   double dtend_sec;
   double rate_MiBs;
   int callingStackID;
} vfd_message_t;

typedef struct vfd_type vfd_t;
struct vfd_type {
   char *filepath;
   char *filename;
   vfd_header_t *header;
   int maxlevel;
   vfd_stack_sample_t *stack_samples;
   vfd_message_t *messages;
   vfd_stack_entry_t *stacks;
   vfd_t *prev;
   vfd_t *next;
};

#endif
