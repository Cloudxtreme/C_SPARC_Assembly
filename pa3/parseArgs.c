/*
 * Filename: parseArgs.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Parses command line args and fills the struct argInfo and 
 * 		fills in the struct errorInfo	
 * Date: 2/23/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */

#include <stdio.h>
#include <unistd.h>     // Needed for getopt()

#include "pa3.h"        // Needed for function prototypes, and stuff
#include "pa3Strings.h" // Needed for string messages

/*
 * Function name: parseArgs() 
 *
 * Function Prototype:
 * void parseArgs( int argc, char *const argv[], struct argInfo *argInfo, 
 * 		    struct errorInfo *errorInfo );	
 *
 * Description: Parses command line args and fills the struct argInfo and 
 * 		struct errorInfo. Parses flags using getopt(). Set the fields
 * 		in struct argInfo based on char and arguments found by 
 * 		getopt(). Returns error for invalid flags (sets 
 * 		ERR_INV_FLAG_OR_ARG). Checks for other flag errors
 * 		such as mutual eclusivity. Initializes defaults into
 * 		fields of argInfo, and initilizes ERROR_NONE into
 * 		errorInfo.
 *
 * Parameters: 
 *      arg 1 - int argc -- number of command line args 
 *      arg 2 - char *const argv[] -- string of command line args
 *      arg 3 - struct argInfo *argInfo -- argInfo struct
 *      arg 4 - struct errorInfo *errorInfo -- errorInfo struct
 *                                                 
 * Side Effects: Parses all command line arguments, and checks to see if they 
 * 		 are good, then fills out the appropriate fields of argInfo
 * 		 struct.
 *
 * Error Conditions: If there were invalid or wrong number of command line args
 *
 * Return Value: None
 */

void
parseArgs( int argc, char *const argv[], struct argInfo *argInfo, 
	         struct errorInfo *errorInfo ) {
  /* Local Variables */
  int opt;      // holds value of command line arg read from getopt()
  
  // Default program Mode & DB
  argInfo->programMode = MODE_FIND_ANAGRAMS;
  argInfo->anagramDB = STR_DEF_ANAGRAM_DB;

  // while loop to parse args using getopt()
  while( (opt = getopt(argc, argv, ARG_STR_NON_EC)) != -1) {
    switch(opt) {
      // argument was -d
      case CHAR_DICT_FLAG:
        argInfo->dictFilename = optarg;
        argInfo->programMode = MODE_SETUP_DB;
        argInfo->flags |= DICT_FLAG;
        break;
      // argument was -h
      case CHAR_HELP_FLAG:
        argInfo->programMode = MODE_USAGE;
        argInfo->flags |= HELP_FLAG;
        break;
      // argument was -o
      case CHAR_DB_DEST_FLAG:
        argInfo->programMode = MODE_SETUP_DB;
        argInfo->flags |= DB_DEST_FLAG;
        break;
      // argument was -s
      case CHAR_DB_SRC_FLAG:
        argInfo->programMode = MODE_SETUP_DB;
        argInfo->flags |= DB_SRC_FLAG;
        argInfo->anagramDB = optarg;
        break;
      // invalid argument
      default:
         argInfo->flags |= ERR_FLAG;
    }
    
    // check if arg was not equal to any of the flags, if so then set error 
    // that flag or arg was invalid
    if( ((argInfo->flags & DICT_FLAG) != DICT_FLAG) ||
        ((argInfo->flags & HELP_FLAG) != HELP_FLAG) ||
        ((argInfo->flags & DB_DEST_FLAG) != DB_DEST_FLAG) ||
        ((argInfo->flags & DB_SRC_FLAG) != DB_SRC_FLAG) ||
        ((argInfo->flags & ERR_FLAG) != ERR_FLAG)) {
      setErrorInfo(errorInfo, ERR_INV_FLAG_OR_ARG, NULL); 
    }
    // mutual exclusion checking
    else if( ((argInfo->flags & DB_SRC_FLAG) == DB_SRC_FLAG) && 
              ((argInfo->flags & DICT_FLAG) == DICT_FLAG) ) {
      setErrorInfo(errorInfo, ERR_MUTUAL_EXCL, STR_ERR_MUTUAL_EXCL);
    }
    else if( ((argInfo->flags & DB_SRC_FLAG) == DB_SRC_FLAG) &&
             ((argInfo->flags & DB_DEST_FLAG) == DB_DEST_FLAG) ) {
      setErrorInfo(errorInfo, ERR_MUTUAL_EXCL, STR_ERR_MUTUAL_EXCL);
    }
    // if there were too many args
    else if ( optind < argc ) {
      setErrorInfo(errorInfo, ERR_EXTRA_ARGS_M, STR_ERR_EXTRA_ARGS);
    }
  }
}
