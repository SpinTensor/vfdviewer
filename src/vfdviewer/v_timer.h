#ifndef V_TIMER_H
#define V_TIMER_H

#include <time.h>

// return the current time
struct timespec current_time();

// returns the time difference of its two arguments
// assuming time2 > time1
double timediff(struct timespec time1, struct timespec time2);

#endif
