/*
 * File: pa4gettimeofday.c
 * Author: TODO
 * UserId: TODO
 * Description: Get time of day. Needed for grading purposes.
 */

#include <sys/time.h>

int pa4gettimeofday( struct timeval *tp, struct timezone *tzp ) {
  return gettimeofday( tp, tzp );
}
