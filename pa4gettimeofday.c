/*
 * File: pa4gettimeofday.c
 * Author: Moiz Qureshi 
 * UserId: cs30xix
 * Description: Get time of day. Needed for grading purposes.
 */

#include <sys/time.h>

/*
 * Function Name: pa4gettimeofday()
 *
 * Function Prototype: 
 *  int pa4gettimeofday( struct timeval *tp, struct timezone *tzp );
 *
 * Description: Gets the epoch time in seconds since 1/1/70 and stores it
 *              into struct timeval *tp.
 *
 * Parameters: 
 *    arg 1 - struct timeval *tp -- holds epoch time in seconds
 *    arg 2 - struct timezone *tzp -- used for timezone, use NULL here though
 *
 * Side Effects: Gets epoch time in seconds and stores in struct timeval *tp
 *
 * Error Conditions: None
 *
 * Return Values: int, but will (void) return value
 */
int pa4gettimeofday( struct timeval *tp, struct timezone *tzp ) {
  return gettimeofday( tp, tzp );
}
