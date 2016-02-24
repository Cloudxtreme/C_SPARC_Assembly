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

#include <stdlib.h>     // Needed for file functions
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
  switch(errorInfo->errorCode) {
  
    case ERR_NONE:
    

    case ERR_ERRNO_M



    case ERR_DB_WRITE_M


    case ERR_INV_FLAG_OR_ARG


    case ERR_MUTUAL_EXCL


    case ERR_DB_PARSE


    case ERR_DB_DEST_FLAG_DEPENDENCE

    case ERR_EXTRA_ARGS_M


    case ERR_USER_INTERFACE


    case ERR_CREATE_ANAGRAM

  
  }
  



}

