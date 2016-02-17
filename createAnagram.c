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

  // Var to hold lenght of src string
  int len = 0; 
  

  len = strlen( src ) + 1;

  anagram->word = (char *) calloc( len, sizeof( char )); 
  strncpy( anagram->word, src, len );

  printf("%s\n", anagram->word );


  return 0;










}
