#ifndef VFD_TYPES_H
#define VFD_TYPES_H

#include <stdbool.h>

#include "vgtk_types.h"
#include "vgtk_colors.h"

typedef struct {
   int vfd_version;
   char *package_string;
   char *datestr_start;
   char *datestr_end;
   long long interval;
   int nprocesses;
   int processID;
   int nthreads;
   double runtime;
   unsigned int function_samplecount;
   unsigned int message_samplecount;
   unsigned int fcallscount;
   unsigned int nstacks;
   long int samples_offset;
   long int stacks_offset;
   long int threadtree_offset;
   unsigned int msgregsendcount;
   unsigned int msgregrecvcount;
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
   int threadID;
   bool precise;
   int namelen;
   char *name;
   vgtk_color_t drawcolor;
   unsigned int num_called;
   unsigned int num_calls;
   double excl_time;
   double incl_time;
   bool visible_in_treeview;
   bool visible_in_listview;
};

typedef struct {
   vfd_sample_kind_enum kind;
   int stackID;
   long long sampletime;
} vfd_stack_sample_t;

typedef struct {
   int threadID;
   int parent_thread;
   int nchildren;
   int *children;
   int level;
} thread_t;

typedef struct {
   int stackID;
   double entry_time;
   double exit_time;
} vfd_fcall_t;

typedef struct {
   double entry_time;
   double exit_time;
} vfd_msgreg_t;

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
   double time_sec;
   double rate_MiBs;
   int callingStackID;
   int callingThreadID;
} vfd_message_sample_t;

typedef struct {
   int n_hw_obs;
   int n_formulae;
   char **hw_obs_names;
   char **te_var_names;
   char **scen_expr_names;
   char **scen_expr_formulae;
   bool *scen_expr_integrated;
} vfd_hwc_header_t;

typedef struct {
   double **observables;
} vfd_hwc_sample_t;

typedef struct vfd_type vfd_t;
struct vfd_type {
   char *filepath;
   char *filename;
   vfd_header_t *header;
   vfd_hwc_header_t *hwc_header;
   int maxlevel;
   vfd_stack_sample_t *stack_samples;
   vfd_fcall_t *fcalls;
   vfd_msgreg_t *msgregs_send;
   vfd_msgreg_t *msgregs_recv;
   vfd_message_sample_t *message_samples;
   vfd_stack_entry_t *stacks;
   vfd_hwc_sample_t *hwc_samples;
   vgtk_handles_t *vgtk_handles;
   vfd_t *prev;
   vfd_t *next;
};

#endif
