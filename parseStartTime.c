/*
 * Filename: parseStartTime.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: This file hold the function for parseStartTime which will 
 *              convert the string into long values and store them into an 
 *              array after checking to see if the values are valid and within
 *              range.       
 * Date: 2/2/16
 * Sources of Help: PA2 Assignment Sheet, PA2 Discussion Slides pt.1
 */

/*
 * Header files included here.
 * Std C Lib header files first, then local headers.
 */

/* Local Headers */
#include <stdio.h>
#include <strings.h>
#include <errno.h>
#include "pa2.h"
#include "pa2Strings.h"

/*
 * Function name: parseStartTime()
 * Function prototype: unsigned long parseStartTime( long clockDecimal[], 
 *                                                   const char * time );
 * Description: This function parses the time string passed in (which was 
 *              passed in as command line argument into this program), and
 *              populates the clockDecimal array according.          
 * 
 * Parameters:
 *      long clockDecimal[] -- arg 1 -- array where time input will be stored
 *      const char * time   -- arg 2 -- pointer to string we will parse
 * 
 * Side Effects: Parses string into and puts values into array. 
 *              
 * Error Conditions: 
 *      Returns errors for two cases: 1) Value is invalid
 *                                    2) Value is out of range
 *      Error Return hex values defined in pa2.h
 *                 
 * Return Value: 
 *      If there are no errors, then 0 is returned.
 *      If there are errors, then the corresponding error hex value is returned
 *      which are checked in the order as described in pa2.h
 */

unsigned long
parseStartTime( long clockDecimal[], const char * time ) {
    
  /* Local Variable Definitions */
  
  long errorCode = 0;
  long hours = 0;
  long mins = 0;
  long secs = 0;
  
  int i;
  
  // Integer to hold value of length of string from time
  int stringLength = 0;

  // Integer variable to hold count of # of colons in string containing time
  int colonCount = 0;

  // Declare tempTime string where copy of time will be stored. Create with
  // size of BUFSIZ (defined in stdio.h)
  char tempTime[BUFSIZ]; 
  
  char *colonPtr1;
  char *colonPtr2;
  char *endptr;

  // Make copy of string time, and store into tempTime
  strncpy( tempTime, time, BUFSIZ );
  
  stringLength = strlen( tempTime );
  for ( i = 0; i < stringLength; i++ ) {
    if ( tempTime[i] == TIME_STR_DELIMITER ) {
      colonCount++;
    }
  }
  
  if( colonCount == REQ_SEPARATORS ) {
    
    colonPtr1 = strchr( tempTime, TIME_STR_DELIMITER );
    colonPtr1[0] = '\0';
    
    errno = 0;
    hours = strtol( tempTime, &endptr, BASE );
    if( errno != 0 || *endptr != NULL ) {
      errorCode =  ERR_HR_VALUE;
    }
    if( checkRange( MIN_HR, HR_OFFSET, hours ) != 1 ) {
      errorCode |= ERR_HR_RANGE;
    }
    
    colonPtr1++;
    colonPtr2 = strchr( colonPtr1, TIME_STR_DELIMITER );
    colonPtr2[0] = '\0';

    errno = 0;
    mins = strtol( colonPtr1 , &endptr, BASE );
    if( errno != 0 || *endptr != NULL ) {
      errorCode |= ERR_MIN_VALUE;
    }
    if( checkRange( MIN_MINUTE, MINUTE_OFFSET, mins ) != 1 ) {
      errorCode |= ERR_MIN_RANGE;
    }
    
    colonPtr2++;
    errno = 0;
    secs = strtol( colonPtr2, &endptr, BASE );
    if( errno != 0 || *endptr != NULL) {
      errorCode |= ERR_SEC_VALUE;
    }
    if( checkRange( MIN_SEC, SEC_OFFSET, secs ) != 1 ) {
      errorCode |= ERR_SEC_RANGE;
    }
    
    clockDecimal[HR_INDEX] = hours;
    clockDecimal[MIN_INDEX] = mins;
    clockDecimal[SEC_INDEX] = secs;

  } else {
    errorCode = ERR_TIME_FORMAT;
    return errorCode;
  }


  return errorCode;
}
