/*
 * Filename: printErrors.c  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Prints the errors in errorInfo struct.
 * Date: 2/23/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */

#include <stdio.h>
#include "pa3.h"        // Needed for function prototypes, and stuff
#include "pa3Strings.h" // Needed for string messages

/*
 * Function name: printErrors() 
 *
 * Function prototype: 
 *  void printErros( const struct errorInfo *errorInfo, const char *progName );
 *
 * Description: Prints the errors in errorInfo struct. Check error member of 
 *              errorInfo if it equals any error constants listed in pa3.h
 *              Print corresponding error messages. If there was an errno
 *              error use perror() to print that error, otherwise use fprintf()
 *              to print the error, also pass in errorMsg string for error 
 *              codes that end with _M. If ANY errors were encountered call 
 *              usage() and print the short usage string to stderr.
 *             
 * Parameters: 
 *      arg 1 - const struct errorInfo *errorInfo -- struct where errors are 
 *      arg 2 - const char *progName -- holds value of program Name
 *                                                 
 * Side Effects: Prints all errors and usage short error.
 *
 * Error Conditions: None
 *
 * Return Value: None
 */

void
printErrors( const struct errorInfo *errorInfo, const char *progName ) {
  int errorPresent = 0;
  switch(errorInfo->errorCode) { 
    
    /* For all errorCodes, except for ERR_NONE, print error to stderr, with
     * appropriate error string. For _M errors also pass in errorMsg.
     * For errno error use perror()
     */

    // No Errors
    case ERR_NONE:
      return;
    
    // Errno Error
    case ERR_ERRNO_M:
      perror(errorInfo->errorMsg);
      errorPresent = 1;
      break;

    // DB Write Error
    case ERR_DB_WRITE_M:
      fprintf(stderr, STR_ERR_DB_WRITE, errorInfo->errorMsg);
      errorPresent = 1;
      break;
  
    // Invalid Flag or Arg Error
    case ERR_INV_FLAG_OR_ARG:
      errorPresent = 1;
      break;
    
    // Mutual Exclusivity Flag Error
    case ERR_MUTUAL_EXCL:
      fprintf(stderr, STR_ERR_MUTUAL_EXCL);
      errorPresent = 1;
      break;

    // parseDB() Error
    case ERR_DB_PARSE:
      fprintf(stderr, STR_ERR_DB_PARSE);
      errorPresent = 1;
      break;
  
    // Databsse Destination Flag Error
    case ERR_DB_DEST_FLAG_DEPENDENCE:
      fprintf(stderr, STR_ERR_DB_DEST_FLAG_DEPENDENCE);
      errorPresent = 1;
      break;

      // Too many args Error
    case ERR_EXTRA_ARGS_M:
      fprintf(stderr, STR_ERR_EXTRA_ARGS, errorInfo->errorMsg);
      errorPresent = 1;
      break;

    // userInterface() Error
    case ERR_USER_INTERFACE:
      fprintf(stderr, STR_ERR_USER_INTERFACE);
      errorPresent = 1;
      break;

    // createAnagram() Error
    case ERR_CREATE_ANAGRAM:
      fprintf(stderr, STR_ERR_CREATE_ANAGRAM);
      errorPresent = 1;
      break;    
  }
  // If errorPresent was set then print the usage short message
  if( errorPresent == 1 ) {
      usage(stderr, USAGE_SHORT, progName);
  }
}

