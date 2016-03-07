/*
 * File: pa4gettimeofday.c
 * Author: Moiz Qureshi 
 * UserId: cs30xix
 * Description: Get time of day. Needed for grading purposes.
 */

#include <sys/time.h>

int pa4gettimeofday( struct timeval *tp, struct timezone *tzp ) {
  return gettimeofday( tp, tzp );
}
