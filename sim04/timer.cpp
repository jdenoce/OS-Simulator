#include "timer.h"

//Constructor, starts timer
Timer::Timer()
{
  start();
}

//Destructor
Timer::~Timer()
{

}

//Starts timer and gets start time
void Timer::start() 
{
  gettimeofday(&time, 0);
  start_time = time.tv_sec * 1000000 + time.tv_usec;
}

//Returns elapsed time
long double Timer::elapsed_time()
{
  gettimeofday(&time, 0);
  return (time.tv_sec * 1000000 + time.tv_usec - start_time) / 1000000;
}

//Returns elapsed time in milliseconds
long double Timer::elapsed_milli()
{
  gettimeofday(&time, 0);
  return (time.tv_sec * 1000000 + time.tv_usec - start_time) / 1000;
}


