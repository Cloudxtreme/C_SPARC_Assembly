/*
 * Filename: writeAnagramToDB.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Writes value of struct anagram to file stream
 * Date: 2/17/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.1
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>      
#include <stdlib.h>     // Needed for fwrite()
#include <string.h>     // Needed for strlen
#include "pa3.h"        // Needed for function prototypes

/*
 * Function name: writeAnagramToDB()
 *
 * Function prototype: 
 *     int writeAnagramToDB( const struct anagram *anagram, FILE *strem );
 *
 * Description: Writes members of anagram struct, that is passed in, to the 
 *              file stream, that is also passed in. First the word is 
 *              printed to the stream, followed, by a null character, then
 *              the hashKey value is printed to the stream, followed by
 *              the newline character.
 * Parameters: 
 *      arg 1 - const struct anagram *anagram -- anagram struct that will be 
 *                                               printed to file stream
 *      arg 2 - FILE *stream -- file where the anagram struct will be 
 *                              printed to.
 *
 * Side Effects: Prints members of anagram struct to file
 *               
 * Error Conditions: If fwrite() returns a non-zero integer, then writing of an
 *                   an element of anagram struct to file has failed.
 *      
 * Return Value: 
 *        0 - fwrite() wrote elements of anagram struct successfuly
 *        1 - fwrite() failed in writing elements of anagram struct
 */

int
writeAnagramToDB( const struct anagram *anagram, FILE *stream ) {
  
  /* Local Variable */
  int returnCode = 0;     // Var to hold return value for this function
  int writeCount = 0;     // Var to hold error for fwrite()
  
  char newline = '\n';    // Var to hold newline char
  char nullchar = '\0';   // Var to hold null char

  /* Write the anagram's word to the file, and store return value into 
   * writeCount, so we can check to see correct number of items were
   * written to the file, if it isnt, then set returnCode
   */
  writeCount = fwrite( anagram->word, sizeof(char), strlen(anagram->word), 
                       stream );
  if ( writeCount != strlen(anagram->word) ) {
    returnCode = 1;
  } 
  
  /* Write the null char to the file next, and store return value into 
   * writeCount, so we can check to see correct number of items were
   * written to the file, if it isnt, then set returnCode
   */
  writeCount = fwrite( &nullchar, sizeof(char), 1, stream );
  if ( writeCount != 1) {
    returnCode = 1;
  } 

  /* Write the anagram's hashKey to the file next, and store return value into 
   * writeCount, so we can check to see correct number of items were
   * written to the file, if it isnt, then set returnCode
   */
  writeCount = fwrite( &(anagram->hashKey), sizeof(int), 1, stream );
  if ( writeCount != 1) {
    returnCode = 1;
  } 

  /* Write the newline char to the file, and store return value into 
   * writeCount, so we can check to see correct number of items were
   * written to the file, if it isnt, then set returnCode
   */
  writeCount = fwrite( &newline, sizeof(char), 1, stream );
  if ( writeCount != 1) {
    returnCode = 1;
  } 
  
  // Return returnCode; may have been set if fwrite() had error
  return returnCode;
}

