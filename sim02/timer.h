#include <iostream>
#include <sys/time.h>
#ifndef TIMER_H
#define TIMER_H

class Timer {
 public:
  Timer();
  ~Timer();

  void start();
  long double elapsed_time();
  long double elapsed_milli();
  
 private:
  struct timeval time;
  double long start_time;
};

#endif
