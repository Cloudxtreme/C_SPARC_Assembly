/*
 * Filename: parseDB.c  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Reads the anagrams DB file into memory, sorts the struct 
 *              anagrams according to their hashKey and word members
 *              
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

/*
 * Function name: parseDB()
 *
 * Function prototype: 
 *      int parseDB( FILE *stream, struct anagramInfo *angramInfo );
 *
 * Description: Reads one anagram at a time from the file stream using
 *                readAnagramFromDB(), if no error is encountered here
 *                then use realloc to increase size of a dynamin array
 *                of struct anagrams, use a temp pointer to not overwrite
 *                ptr from previously allocated data if realloc fails.
 *                If realloc fails, free the allocated memory. Then save the
 *                read anagram into newly allocated memory. After all the 
 *                anagram structs from the file, use qsort to sort them, using
 *                anagramCompare() as the compare function. Finally write the 
 *                pointer to the array and number of elements in the array into
 *                anagramInfo.             
 *          
 * Parameters: 
 *      arg 1 - FILE *stream -- file we are reading anagrams structs from 
 *      arg 2 - struct anagramInfo *anagramInfo -- struct containing array
 *                                                 of anagrams and number of
 *                                                 anagrams
 *                                                 
 * Side Effects: Reads allt he struct anagrams from the database file and 
 *               stores them into memory in the anagramInfo struct.
 *                            
 * Error Conditions: If realloc() or readAnagramFromDB() fails                 
 *      
 * Return Value: 
 *    0 - succesfull - read all anagram structs from DB and stored into 
 *                     anagramInfo
 *    1 - total failure
 */

int
parseDB( FILE *stream, struct anagramInfo *anagramInfo ) {
   
  /* Local Variables */

  struct anagram *anagramArrPtr = NULL;
  struct anagram *anagramTmpPtr = NULL;
  struct anagram tmpAnagram;
  
  int size = 0;
  int readErr = 0;

  while( (readErr = readAnagramFromDB(stream, &tmpAnagram)) )  {
    if( readErr == -1) {
      return 1;
    }
    if( readErr == 1 ) {
      anagramTmpPtr = (struct anagram *) realloc( anagramTmpPtr,
                                                 sizeof(struct anagram) );
      if( anagramTmpPtr != NULL) {
        anagramArrPtr = anagramTmpPtr;
        *anagramArrPtr = tmpAnagram;

      } else {
        return 1; 
      }
    }
    if( readErr == 0 ) {
      break;
    }
  }
  
  size = (sizeof(anagramArrPtr)/sizeof(struct anagram));
  qsort( anagramArrPtr, size, sizeof(struct anagram), anagramCompare );  

  anagramInfo->anagramPtr = anagramArrPtr;
  anagramInfo->numOfAnagrams = size;=

  return 0;
}
