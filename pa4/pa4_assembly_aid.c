/*
 * Filename: pa4.c (Helper file so I can convert this code to assembly) 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Helper File for pa4.s Will convert this code to assembly in 
 *              pa4.s. This is a driver for the myUniq program, that calls 
 *              runUniq() and printError().
 * Date: 3/6/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>
#include <stdlib.h>

#include "pa4.h"
#include "pa4Strings.h"
/*
 * Function name: main()
 *
 * Function prototype: int main( int argc, char *argv[] );
 *
 * Description: This is a helper file for pa4.s. It is the C version of the 
 *              that file, which I will use to convert to assembly. This is 
 *              where main() is located and acts as the driver for the program 
 *              for myUniq by calling runUniq() and printErrors()
 *          
 * Parameters: 
 *      arg 1 - int argc -- number of arguments passed in
 *      arg 2 - char *argv[] --array of strings that are the arguments
 *
 * Side Effects: Runs the myUniq program 
 *              
 * Error Conditions: No error occurs in main(), however there are errors that
 *                   can occur in runUniq() and the functions that it calls. 
 *                   Errors are recored in errorInfo struct, and printErrors()
 *                   will report them
 *      
 * Return Value: 
 *  EXIT_SUCCESS - if there were no errors
 *  EXIT_FAILURE - if there was an error
 */

int 
main( int argc, char *argv[] ) {
  struct errorInfo errorInfoPtr;
  struct argInfo argInfoPtr;
  
  // Used to find size of struct errorInfo and argInfo
  //printf("%d\n", sizeof(struct errorInfo));
  //printf("%d\n", sizeof(struct argInfo));

  parseArgs(argc, argv, &argInfoPtr, &errorInfoPtr);

  if(errorInfoPtr.errorCode == ErrNone) {
    if((argInfoPtr.options & OPT_HELP) == OPT_HELP) {
      usage(stdout, UsageLong, argv[0]);
      return EXIT_SUCCESS;
    } else {
      runUniq(&argInfoPtr, &errorInfoPtr);
      if(errorInfoPtr.errorCode != ErrNone) {
        printErrors(&errorInfoPtr, argv[0]);
        return EXIT_FAILURE;
      }
    }
  } else {
    printErrors(&errorInfoPtr, argv[0]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
