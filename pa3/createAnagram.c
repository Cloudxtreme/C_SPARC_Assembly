/*
 * Filename: createAnagram.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Dynamically allocates and populates anagram struct according to
 *              source parameters passed in.
 * Date: 2/17/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.1
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>    
#include <stdlib.h>     // Needed for calloc()
#include <string.h>     // Needed for strlen

#include "pa3.h"        // Needed for function calls
/*
 * Function name: createAnagram() 
 *
 * Function prototype: 
 *    int createAnagram( const char *src, struct anagram *anagram );
 *
 * Description: Dynamically allocates memory an populates struct anagram,
 *              with src string, computes hash and populates that field 
 *              of anagram struct as well
 *          
 * Parameters: 
 *      arg 1 - const char *src -- source string of word that we need to 
 *                                 allocate memory for and and store into
 *                                 anagram struct
 *      arg 2 - struct anagram *anagram -- anagram which we will be 
 *                                         populating members for
 *
 * Side Effects: Dynaically allocates enough memory size of source string
 *               and stores it into the anagram struct, calculates hash of 
 *               the word, and stores that into anagram struct as well
 *              
 * Error Conditions: If calloc() fails  
 *      
 * Return Value: 
 *      0 - success in allocating memory and populating anagram struct fields
 *      1 - dynamic memory allocation fails (calloc() fails)
 */

int
createAnagram( const char *src, struct anagram *anagram ) {
  /* Local Variables */

  // Var to hold length of src string
  int len = 0; 
  
  // Var to hold value of return status
  int returnCode = 0;

  // Var to hold calculated hash
  int hash = 0;

  // Var to hold lowercase src string
  char lowerCaseString[BUFSIZ];

  // Get length of source string+1, accounting for null char
  len = strlen( src ) + 1;
 
  /* Get lowercase version of source string and store into lowerCaseString,
   * then calculate hash by calling hashString() function, then
   * set the anagram hashKey value accordingly
   */
  lowerCaseSortString( src, len, lowerCaseString );
  hash = hashString( lowerCaseString );
  anagram->hashKey = hash;          

  /* Allocate enough memory (size of src string). If calloc fails then
   * then set returnCode to 1, otherwise if it passes then set returnCode 
   * to 0, and copy src string into anagram word string
   */
  anagram->word = (char *) calloc( len, sizeof( char )); 
  if ( anagram->word != NULL ) {
    strncpy( anagram->word, src, len );
    returnCode = 0;
  } else {
    returnCode = 1;
  }
  
  // Return returnCode, either 0 or 1 if calloc passed or failed, respectively
  return returnCode;
}
