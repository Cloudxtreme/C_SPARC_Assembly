/*
 * Filename: parseArgs.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Parses command line args and fills the struct argInfo and 
 *              struct errorInfo
 *             
 * Date: 3/1/16
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.1, 
 *                  man page for getopt_long
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>
#include <unistd.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function name: parseArgs() 
 *
 * Function prototype: 
 *  void parseArgs( int argc, char *const argv[], struct argInfo *argInfo,
 *                  struct errorInfo *errorInfo );
 *
 * Description: Parses command line args and fills the struct argInfo and 
 *              the struct errorInfo accordingly. Uses the getop_long() 
 *              function for parsing of the argumnets.
 *          
 * Parameters: 
 *      arg 1 - int argc -- number of command line argumnets
 *      arg 2 - char *const argv[] -- array of strings of command line 
 *                                    arguments
 *      arg 3 - struct argInfo *argInfo -- argInfo struct
 *      arg 4 - struct errorInfo *errorInfo - errorInfo struct
 *
 * Side Effects: Parses the command line arguments and fills out the argInfo
 *               and errorInfo structs.
 *               
 * Error Conditions:
 *    if getopt_long() indicates an invalid flag
 *    if extra command line arguments were entered
 *    if mutually exclusive flags were used together
 *      
 * Return Value: None
 */

void 
parseArgs( int argc, char *const argv[], struct argInfo *argInfo, 
           struct errorInfo *errorInfo ) {
  /* Local Variable */
  // necessary struct for long options, used in getopt_long()
  static struct option long_options [] = {
    { STR_LONG_OPT_COUNT, 0, NULL, FLAG_COUNT },
    { STR_LONG_OPT_IGNORE_CASE, 0, NULL, FLAG_IGNORE_CASE },
    { STR_LONG_OPT_SORT_OUTPUT, 0, NULL, FLAG_SORT_OUTPUT },
    { STR_LONG_OPT_SORT_INPUT, 0, NULL, FLAG_SORT_INPUT },
    { STR_LONG_OPT_SUMMARY, 0, NULL, FLAG_SUMMARY },
    { STR_LONG_OPT_HELP, 0, NULL, FLAG_HELP },
    { STR_LONG_OPT_DUP_ONLY, 0, NULL, FLAG_DUP_ONLY },
    { STR_LONG_OPT_DUP_ALL, 0, NULL, FLAG_DUP_ALL },
    { STR_LONG_OPT_UNIQUE, 0, NULL, FLAG_UNIQUE }
  }

  int opt_ind = 0;    // counts number of option flags
  int opt;            // hold value of option flags, use in swtich-case
  
  // Set default argInfo parameters
  argInfo->options = 0;
  argInfo->outputMode = Regular;
  argInfo->inFile = NULL;
  argInfo->outFile = NULL;

  // Set default errorInfo parameters
  errorInfo->errorCode = ErrNone;
  errorInfo->errorMsg = NULL;
  
  // while loop to parse arguments using getopt_long()
  while( (opt = getopt_long(argc, argv, ARG_STRING_NON_EC, long_options,
          &opt_ind) != -1) ) {
    // use switch-case to see what flags were present in option
    switch(opt) {
      // option had -c flag
      case FLAG_COUNT:
        argInfo->options |= OPT_COUNT;
        break;

      // option had -i flag
      case FLAG_IGNORE_CASE:
        argInfo->options |= OPT_IGNORE_CASE;
        break;

      // option had -s flag
      case FLAG_SORT_OUTPUT:
        argInfo->options |= OPT_SORT_OUTPUT;
        break;

      // option had -S flag
      case FLAG_SORT_INPUT:
        argInfo->options |= OPT_SORT_INPUT;
        break;

      // option had -x flag
      case FLAG_SUMMARY:
        argInfo->options |= OPT_SUMMARY;
        break;

      // option had -h flag
      case FLAG_HELP:
        argInfo->options |= OPT_HELP
        break;

      // option had -d flag
      case FLAG_DUP_ONLY:
        argInfo->outputMode = DuplicateOnly;
        break;

      // option had -D flag
      case FLAG_DUP_ALL:
        argInfo->outputMode = DuplicateAll;
        break;

      // option had -u flag
      case FLAG_UNIQUE:
        argInfo->outputMode = Unique;
        break;
      
      // required default case - don't do anything
      default:
      
    }               
  }




  
 
}
