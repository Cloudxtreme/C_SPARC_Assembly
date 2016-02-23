/*
 * Filename: testuserInterface.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: Tester for userInterface()
 */

#include <stdio.h>

#include "pa3.h"
#include "test.h"


/*
 * TODO Function headers are always needed!
 */
static void testuserInterface() {
              
  struct anagram arrayAnagram[5];      
  struct anagramInfo anagramInfo;
  
  anagramInfo.numOfAnagrams = 5;
  
  arrayAnagram[0].word = "tops";
  arrayAnagram[0].hashKey = 10030661;

  arrayAnagram[1].word = "hello";
  arrayAnagram[1].hashKey = 296885189;

  arrayAnagram[2].word = "olleh";
  arrayAnagram[2].hashKey = 296885189;

  
  arrayAnagram[3].word = "loleh";
  arrayAnagram[3].hashKey = 296885189;

  
  arrayAnagram[4].word = "elloh";
  arrayAnagram[4].hashKey = 296885189;


  anagramInfo.anagramPtr = arrayAnagram;

  userInterface(&anagramInfo);



}

/*
 * TODO Function headers are always needed!
 */
int main( void ) {
  (void) fprintf( stderr, "Starting testuserInterface\n" );

  testuserInterface();

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}


