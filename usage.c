/*
 * Filename: usgae.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Prints out the usgae message of the program 
 * Date: 2/7/16
 * Sources of Help: PA2 Assignment Sheet, PA2 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>
#include "pa2.h"
#include "pa2Strings.h"

/*
 * Function name: usage()
 *
 * Function prototype: void usage( const char * programName );
 *
 * Description: Prints out the name of the program and the program's usage 
 *              message. *             
 *            
 * 
 * Parameters: 
 *      arg 1 - const char * programName - name of the program
 * 
 * Side Effects: Prints the program's name and the usage message *             
 *              
 * Error Conditions: None
 *      
 * Return Value: None
 */

void
usage( const char * programName ) {

  // Call printf() and pass in parameters correctly
  printf( STR_USAGE, programName, MIN_HR, HR_OFFSET, MIN_MINUTE, MINUTE_OFFSET,
          MIN_SEC, SEC_OFFSET, MIN_INTERVAL, MAX_INTERVAL, DEF_INTERVAL, 
          MIN_TICKS, MAX_TICKS, DEF_TICKS );
}

