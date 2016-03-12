/*
 * Filename: findAnagrams.c  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Opens the database and searches for anagrams
 * Date: 2/23/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */

#include <stdlib.h>     // Needed for file functions
#include <errno.h>      // Needed for errno

#include "pa3.h"        // Needed for function prototypes, and stuff
#include "pa3Strings.h" // Needed for string messages

#define READ "r"

/*
 * Function name: findAnagrams()
 *
 * Function prototype: 
 *    void findAnagrams( const struct argInfo *argInfo, 
 *                       struct errorInfo *errorInfo ); 
 *
 * Description: Opens the database and searches for angrams. Use fopen() to
 *              open the database source file from argInfo struct. Read the
 *              the database into memory using parseDB(). Call 
 *              userInterface() to search for anagrams. When finished
 *              free memory allocated by parseDB(). Use fclose() to 
 *              close the file
 *             
 * Parameters: 
 *      arg 1 - const struct argIndo *argInfo -- holds filename for DB
 *      arg 2 -  struct errorInfo *errorInfo
 *                                                 
 * Side Effects: Opens the db file, loads the db into memory, calls 
 *                userInterface to search for anagram target, 
 *                frees memory of db loaded into memory, closes the file
 *                            
 * Error Conditions: If userInterface() and parseDB() fails.
 *
 * Return Value: None
 */

void
findAnagrams( const struct argInfo * argInfo, struct errorInfo *errorInfo ) {
  /* Local Variables */
  struct anagramInfo anagramInfo;     // local anagramInfo struct
  
  int errParseDB = 0;                 // holds error from parseDB()
  int errUserInt = 0;                 // holds erro from userInterface()
  int i;                              // loop counter when freeing memory

  /* Set errno to 0. Open the DB file, if error occurs, then set
   * appropriate error flags in errorInfo struct and return, otherwise 
   * continue.
   */
  errno = 0;
  FILE *db = fopen(argInfo->anagramDB, READ);
  if( errno != 0 ) {
    setErrorInfo(errorInfo, ERR_ERRNO_M, argInfo->anagramDB);
    return;
  } else {
    // Call parseDB, store return value for errors
    errParseDB = parseDB(db, &anagramInfo);
    // If return from parseDB was not 0, then set error flags in errorInfo
    // struct appropriately and return, otherwise continue.
    if( errParseDB != 0) {
      setErrorInfo(errorInfo, ERR_DB_PARSE, NULL);
      return;
    }
    // Call userInterface, and store return value in errUserInt
    errUserInt = userInterface( &anagramInfo );
    // If return value from userInterface was not 0, then set error flags 
    // appropriately and return, otherwise continue. 
    if( errUserInt != 0 ) {
      setErrorInfo(errorInfo, ERR_USER_INTERFACE, NULL);
      return;
    }
    // free the memory from calloc of words and realloc of array of anagrams
    // structs.
    for(i = 0; i < anagramInfo.numOfAnagrams; i++) {
      free(anagramInfo.anagramPtr[i].word);
    }
    free(anagramInfo.anagramPtr);
    // Close the db file
    fclose(db);
  }
}
