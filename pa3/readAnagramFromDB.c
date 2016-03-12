/*
 * Filename: readAnagramFromDB.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Reads one anagram from the file stream, and fills in anagran 
 *              struct
 * Date: 2/22/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>      
#include <stdlib.h>     // Needed for fwrite()
#include <string.h>     // Needed for strlen
#include <errno.h>

#include "pa3.h"        // Needed for function prototypes

#define NULLCHAR '\0'

/*
 * Function name: readAnagramFromDB()
 *
 * Function prototype: 
 *    int readAnagramFromDB( FILE * stream, struct anagram *anagram ); 
 *
 * Description: Reads one anagram at a time from the file stream and fills the
 *              members of the anagram struct. Uses fgets() to read a line into
 *              local buffer, then calloc() to dynamically allocate space for
 *              anagram's word member, then uses strncpy() to copy the word in,
 *           
 * Parameters: 
 *      arg 1 - FILE * stream -- database file we are reading from 
 *      arg 2 - struct anagram *anagram -- pointer to anagram we are filling in
 *            
 *
 * Side Effects: Reads anagram from database and populates the anagram that we
 *               are passing in by reference.
 *               
 * Error Conditions: If calloc() fails 
 *                   
 * Return Value: 
 *        0 - if fgets() returns NULL (meaning end of file reached)
 *        1 - if anagram is read correctly from DB
 *       -1 - if an error occurred
 */

int 
readAnagramFromDB( FILE *stream, struct anagram *anagram) {
  
  /* Local Variables */
  char buf[BUFSIZ];       // string to hold line read from db
  char *hashKeyPtr;       // pointer to hold location of haskKey member
  
  // Check to see if we can read a line from db, if not return 0 (EOF)
  if( fgets(buf, BUFSIZ, stream) != NULL ) {
    // use calloc to allocate space for word string
    anagram->word = (char *) calloc( strlen(buf)+1, sizeof(char) );
    // if calloc failed, return -1, otherwise, copy the string from line to 
    // the word member of anagram struct passed in
    if( anagram->word != NULL) {
      strncpy( anagram->word, buf, strlen(buf)+1);
      // set hashKey pointer position at the hashKey location from line read in
      hashKeyPtr = strchr( buf, NULLCHAR ) + 1;
      // Copy 4 bytes starting from hashKeyPtr location, and store that into 
      // hashKey member of anagram struct
      memcpy( &(anagram->hashKey), hashKeyPtr, sizeof(int) );
    } else {
      return -1;
    }
  } else {
    return 0;
  }
  // since anagram was read correctly return 1   
  return 1;
}
