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

#include "pa3.h"        // Needed for lots of program prototypes and defines
#include "pa3Strings.h" // Needed for string constants

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

  // Local anagram struct to hold search word
  struct anagram userAnagram;         

  // anagream struct pointer used in bsearch()
  struct anagram *bsearchPtr;

  // anagram struct used as postion holder in struct array
  struct anagram *matchPtr = NULL;

  // Holds any error values returned from createAnagram()
  int error = 0;

  // Holds word that user will enter
  char userWord [BUFSIZ];

  // char pointer needed to remove newline character from string
  char *charPtr = NULL;

  // First print user prompt message
  printf(STR_ANAGRAM, STR_USER_PROMPT);

  // Continue getting new words until EOF character is typed
  while( fgets(userWord, BUFSIZ, stdin) != NULL ) {
    
    // Replace newline character in read in word with null character
    charPtr = strchr( userWord, NEWLINE );
    *charPtr = NULLCHAR;

    // Create anagram of word read in from user, keep track of any error.
    // If there is an error return 1 immediately.
    error = createAnagram( userWord, &userAnagram );
    if( error != 0 ) {
      return 1;
    }

    // Use bsearch to find matching occurrence of our anagrams strucut, that
    // we created, in the array anagram struct
    bsearchPtr = (struct anagram *)bsearch( &userAnagram, 
                                            anagramInfo->anagramPtr,
                                            anagramInfo->numOfAnagrams,
                                            sizeof(struct anagram),
                                            hashKeyMemberCompare );

    // If bsearch found somethimg then continue inside
    if( bsearchPtr != NULL ) {
      /* Set matchPtr equal to bsearchPtr.
       * Move to each previous anagram struct in the array as long as the 
       * previous anagram has the same hashKey as the local anagram.
       */
      matchPtr = bsearchPtr;
      while( (matchPtr->hashKey) == (bsearchPtr->hashKey) ) {
       matchPtr--;
      } 
      // Move forward one anagram in array so we are at a matching anagram
      matchPtr++;
      // Print found anagrams message string
      printf(STR_ANAGRAM, STR_FOUND_ANAGRAMS);
      // For each consectuive anagram with matching hashKeys, print their word
      while( (matchPtr->hashKey) == (bsearchPtr->hashKey) ) {
        printf(STR_ANAGRAM, matchPtr->word);
        matchPtr++;
      }
      // Print a newline character
      putchar(NEWLINE);
    } else {
      // Since no anagrams were found in bsearch(), print no anagram string
      // message, then print a newline character
      printf(STR_ANAGRAM, STR_NO_ANAGRAMS);
      putchar(NEWLINE);
    }
    // Print the user prompt user again, before we loop back
    printf(STR_ANAGRAM, STR_USER_PROMPT);
  }
  // Since we had success and user has hit ctrl+D, return 0 for success!
  return 0;
}
  
 

