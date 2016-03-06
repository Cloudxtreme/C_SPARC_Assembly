/*
 * Filename: usage.c  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Prints the appropriate usage message to the specified stream
 * Date:3/5/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */

#include <stdio.h>
#include "pa4.h"        // Needed for function prototypes, and stuff
#include "pa4Strings.h" // Needed for string messages

/*
 * Function name: usage()
 *
 * Function prototype: 
 *  void usage( FILE *stream, enum usageMode u, const char *progName );
 *
 * Description: Print the appropriate usage message to the specified stream. 
 *              Use usageMode to print a short usage or long usage message.
 *
 * Parameters: 
 *      arg 1 - FILE *stream -- stdout or stderr 
 *      arg 2 - enum usageMode u -- USAGE_SHORT or USAGE_LONG
 *      arg 3 - const char *progName -- name of program
 *                                                 
 * Side Effects: Prints either short or long usage strings
 *
 * Error Conditions: None
 *
 * Return Value: None
 */

void
usage( FILE *stream, enum usageMode u, const char *progName ) {

  // If usage mode is short, then print short usage string
  if( u == UsageShort ) {
    fprintf(stream, STR_USAGE_SHORT, progName); 
  }
  // If usage mode is long, then pirnt long usage string
  else if( u == UsageLong ) {
    fprintf(stream, STR_USAGE_LONG, progName); 
  }
}


