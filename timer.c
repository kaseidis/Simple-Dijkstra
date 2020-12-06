#include "timer.h"

struct timeval timerStart;

#ifndef timersub
/**
 * Function from: https://github.com/strongswan/strongswan/blob/master/src/libstrongswan/utils/compat/windows.h
 */ 
void timersub(struct timeval *a, struct timeval *b, struct timeval *res)
{
  res->tv_sec = a->tv_sec - b->tv_sec;
  res->tv_usec = a->tv_usec - b->tv_usec;
  if (res->tv_usec < 0)
  {
    res->tv_usec += 1000000;
    res->tv_sec--;
  }
}
#endif

void StartTimer()
{
  gettimeofday(&timerStart, NULL);
}

double GetTimer()
{
  struct timeval timerStop, timerElapsed;
  gettimeofday(&timerStop, NULL);
  timersub(&timerStop, &timerStart, &timerElapsed);

  return timerElapsed.tv_sec * 1000.0 + timerElapsed.tv_usec / 1000.0;
}
