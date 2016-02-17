/*
 * Filename: lowerCaseSortString.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Creates lowercase, alphabetical version of source string
 *              and stores it in destination string.            
 *            
 * Date: 2/16/16
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.1
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>
#include <stdlib.h>   // Needed for qsort()
#include <ctype.h>    // Needed for towlower()
#include <string.h>   // Needed for strncpy()

#include "pa3.h"      // Needed for charCompare()

/*
 * Function name: lowerCaseSortString()
 *
 * Function prototype: 
 *    void lowerCaseSortString( const char *src, size_t n, char *dest );
 *
 * Description: Creates lowercase alphabetical version of string *src and 
 *              stores it in *dest
 *          
 * Parameters: 
 *      arg 1 - const char *src -- source string
 *      arg 2 - size_t n -- size of the destination char array *dest
 *      arg 3 - char *dest -- destination char array        
 *
 * Side Effects: Converts source string to lowercase, sorts the chars, and 
 *               stores them alphabetically into the destination array
 *               *dest
 *               
 * Error Conditions: None 
 *      
 * Return Value: None
 */

void
lowerCaseSortString( const char *src, size_t n, char *dest ) {
  
  // Local Variables
  int i = 0;              // Used as counter for while-loop

  char srcCopy[BUFSIZ];   // String we will copy source string into
  
  // Copy src string into srcCopy
  strncpy( srcCopy, src, n );
  
  // Store lower case letters of srcCopy into dest string
  while( srcCopy[i] ) {
    dest[i] = tolower( srcCopy[i] );
    i++;
  }

  // Sort dest string in alphabetical order
  qsort( dest, strlen( dest ), sizeof(char), charCompare );

}
