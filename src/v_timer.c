#include <time.h>

// return the current time
struct timespec current_time() {
   struct timespec curr_time;
   clock_gettime(CLOCK_MONOTONIC, &curr_time);
   return curr_time;
}

// returns the time difference of its two arguments
// assuming time2 > time1
double timediff(struct timespec time1, struct timespec time2) {
   // difference in second counter
   long long delta_sec = time2.tv_sec - time1.tv_sec;
   // difference in nanosecond counter
   long long delta_nsec = time2.tv_nsec - time1.tv_nsec;
   // handle possible carry over of nanoseconds
   if (delta_nsec < 0) {
      // add one second in nano seconds to the nano second difference
      delta_nsec += 1000000000l;
      // substract one second from the second difference
      delta_sec -= 1l;
   }
   //convert everything to double
   double d_delta_sec = (double) delta_sec;
   double d_delta_nsec = (double) delta_nsec;
   
   // return the amount of seconds (rescaling the nsec counter on the fly)
   return d_delta_sec + d_delta_nsec * 1.0e-9;
}
