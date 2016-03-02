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

  int long_index = 0;
  int option;
  


  argInfo->options = 0;
  argInfo->outputMode = Regular;
  argInfo->inFile = NULL;
  argInfo->outFile = NULL;

  errorInfo->errorCode = ErrNone;
  errorInfo->errorMsg = NULL;
  



}
