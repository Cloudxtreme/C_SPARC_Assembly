/*
 * Filename: setupDB.c  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Takes dictionary file on disk and creates on disk a database
 *              representation of the words within the dictionary
 * Date: 2/17/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.1
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */

#include <stdlib.h>     // Needed for file functions
#include <errno.h>      // Needed for errno
#include <string.h>     // Needed for strchr()

#include "pa3.h"        // Needed for function prototypes, and stuff
#include "pa3Strings.h" // Needed for string messages

#define WRITE_MODE "a"
#define READ_MODE "r"
#define NEWLINE '\n'
#define NULLCHAR '\0'

/*
 * Function name: setupDB()
 *
 * Function prototype: 
 *  void setupDB( const struct argInfo *argInfo, struct errorInfo *errorInfo );
 *
 * Description: Takes a dictionary file on disk and creates on disk a database
 *              representation of the words within the dictionary. The file
 *              names for both the dictionary and database are passed in,
 *              inside the struct argInfo. Will fopen(), the dict file for
 *              reading the database file for writing. fgets() one line at a 
 *              time from the dictionary, creates a new struct anagram by
 *              calling createAnagra(), and writing to the the databse with
 *              writeAnagramToDB(). Error codes are set using struct errorInfo.
 *              Files are closed at the end.
 *          
 * Parameters: 
 *      arg 1 - const struct argInfo *argInfo -- where filenames are located
 *      arg 2 - struct errorInfo *errorInfo -- store errors here
 *
 * Side Effects: Reads dictionary, creates anagram of word, and writes it to 
 *               database. All errors are checked for.
 *              
 * Error Conditions: if fopen() fails, if createAnagram() fails, or if 
 *                   writeAnagramToDB() fails
 *      
 * Return Value: None (struct errorInfo passed in by ref)
 */

void
setupDB( const struct argInfo *argInfo, struct errorInfo *errorInfo ) {
  
  /* Local Variables */
  struct anagram a;
  char buf[BUFSIZ];
  
  int createAnagramErr = 0;
  int writeAnagramErr = 0;

  /* Set errno = 0. Open dictionary file, with given filename from argInfo.
   * If there is error, use setErrorInfo() to set error accoridngly.
   */
  errno = 0;
  FILE *dictionary = fopen( argInfo->dictFilename, READ_MODE );
  if( errno != 0 ) {
    setErrorInfo( errorInfo, ERR_ERRNO_M, argInfo->dictFilename );
  }
  
  /* Set errno = 0. Open database file, with given filename from argInfo.
   * If there is error, use setErrorInfo() to set error accoridngly.
   */
  errno = 0;
  FILE *database = fopen( argInfo->anagramDB, WRITE_MODE );
  if( errno != 0 ) {
    setErrorInfo( errorInfo, ERR_ERRNO_M, argInfo->anagramDB );
  }
 
  /* If dictionary file isnt empty, then read line by line, from the
   * dictionary. For each line, replace the the newline character with
   * a null character, so we ee can strchr on the buf (string of line).
   * Set error int  = 0, create anagram of word read from line string (buf),
   * if there is error then use setErrorInfo() to set errors accordingly.
   * Then set error int  = 0 again, so we can call writeAnagramToDB, using
   * the anagram we just created before, so we can write it to the 
   * database. If there is an error, use setErrorInfo() to set errors
   * accordingly, close file, and return;
   */
  if( dictionary != NULL ) {
    while( fgets(buf, BUFSIZ, dictionary) ) {
      char *endOfWord = strchr(buf, NEWLINE);
      *endOfWord = NULLCHAR;
     
      createAnagramErr = createAnagram( buf, &a );
      if( createAnagramErr != 0 ) {
        setErrorInfo( errorInfo, ERR_CREATE_ANAGRAM, NULL );
        fclose( dictionary );
        fclose( database );
        return;
      }

      writeAnagramErr = writeAnagramToDB( &a, database );
      if( writeAnagramErr != 0 ) {
        setErrorInfo( errorInfo, ERR_DB_WRITE_M, a.word );
        fclose( dictionary );
        fclose( database );
        return;
      }
    }
  }
  
  // Close the database and dictionary files
  fclose( database );
  fclose( dictionary );
    
  // Print db built messaage
  printf( STR_DB_BUILT, argInfo->anagramDB );
}
