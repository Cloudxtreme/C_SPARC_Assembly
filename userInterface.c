/*
 * Filename: userInterface.c  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Gets the next word from the user and prints any matching 
 *              anagrams
 * Date: 2/22/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>      // Needed for fegets()
#include <stdlib.h>     // Needed for bsearch()
#include <string.h>

#include "pa3.h"
#include "pa3Strings.h"

#define NEWLINE  '\n'
#define NULLCHAR  '\0'

/*
 * Function name: userInterface()
 *
 * Function prototype: 
 *      int userInterface( const struct anagramInfo *anagramInfo );
 *  
 * Description: Gets the next word from the user and prints any matching 
 *              anagrams. Use fgets() to get an input word from stdin. 
 *              Use strchr() to replace newline char with null char so string
 *              is null terminated. Then use createAnagram() to populate an
 *              anagram. Then use bsearch() to find that anagram with a 
 *              matching hashKey member (if it exists). Use the
 *              hashKeyMemberCompare() as comparator for bsearch(). If 
 *              there is a match print all adjacent struct anagrams with 
 *              matching hashKey values in alphabetical order. Repeat,
 *              this process until an error occurs or until the user enters
 *              ctrl+D (EOF).
 *          
 * Parameters: 
 *      arg 1 - const struct anagramInfor *anagramInfor -- anagram struct array
 *
 * Side Effects: Finds all matching angrams with same haskKey of the word that
 *               the user inputs from keyboard.
 *               
 * Error Conditions: If the function or any other functions called within this 
 *                   function fail
 *      
 * Return Value: 
 *    0 - this function was successful
 *    1 - this function was unsucessful
 *
 */ 

int  
userInterface( const struct anagramInfo *anagramInfo ) {
  
  /* Local Variable */
  struct anagram userAnagram;
  struct anagram *bsearchPtr;
  struct anagram *matchPtr = NULL;

  int error = 0;

  char userWord [BUFSIZ];
  char *charPtr = NULL;

  
  printf("%s", STR_USER_PROMPT);

  while( fgets(userWord, BUFSIZ, stdin) != NULL ) {
    

    charPtr = strchr( userWord, NEWLINE );
    *charPtr = NULLCHAR;

    error = createAnagram( userWord, &userAnagram );
    if( error != 0 ) {
      return 1;
    }

    bsearchPtr = (struct anagram *)bsearch( &userAnagram, 
                                            anagramInfo->anagramPtr,
                                            anagramInfo->numOfAnagrams,
                                            sizeof(struct anagram),
                                            hashKeyMemberCompare );

    if( bsearchPtr != NULL ) {
      matchPtr = bsearchPtr;
      while( (matchPtr->hashKey) == (bsearchPtr->hashKey) ) {
       matchPtr--;
      } 
    } else {
      break;
    }

    matchPtr++;
    while( (matchPtr->hashKey) == (bsearchPtr->hashKey) ) {
      printf( "%s\n", matchPtr->word );
      matchPtr++;
    }
  }

  return 0;
}
  
 

