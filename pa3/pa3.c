/*
 * Filename: pa3.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Driver for the anagram program 
 * Date: 2/23/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa3.h"        // Needed for function prototypes, and stuff
#include "pa3Strings.h" // Needed for string messages

/*
 * Function name: main() 
 *
 * Function Prototype: int main( int argc, char * argv[] )l
 * 
 * Description: Runs the program by calling other fucntions. Use a struct 
 *              errorInfo to track errors caused by parseArgs(), setupDB(),
 *              or findAnagrams(). Use parseArgs() to parse all the command
 *              line arguments. If no errors, run the program according to 
 *              the mode specified in argInfo struct. If any errors occurred,
 *              the use printErrors().
 *
 * Parameters: 
 *      arg 1 - int argc -- number of command line args 
 *      arg 2 - char *const argv[] -- string of command line args
 *                                                 
 * Side Effects: Runs the anagram program!
 *
 * Error Conditions: None 
 *
 * Return Value: None
 */

int 
main( int argc, char *argv[] ) {
  
  /* Local Variables */
  struct errorInfo errorInfo;   // struct errorInfo to hold errors
  struct argInfo argInfo;       // struct argInfo to hold comman line args info

  // Call parseArgs() 
  parseArgs(argc, argv, &argInfo, &errorInfo);
  
  // If usage mode is USAGE, then print long usage string
  if( argInfo.programMode == MODE_USAGE ) {
    usage(stdout, USAGE_LONG, argv[0]);
  }

  // if usage mode is setup DB then call setupDB
  if( argInfo.programMode == MODE_SETUP_DB ) {
    setupDB(&argInfo, &errorInfo );
  }

  // if usage mode is find anagrams, then call findAnagrams()
  if( argInfo.programMode == MODE_FIND_ANAGRAMS ) {
    findAnagrams(&argInfo, &errorInfo);
  }

  // if there was an error, then call printErrors() and exit with failure
  if(errorInfo.errorCode != ERR_NONE ) {
    printErrors(&errorInfo, argv[0]);
    return EXIT_FAILURE;
  }
  
  // no errors by now so exit with success
  return EXIT_SUCCESS;
  
}
  


