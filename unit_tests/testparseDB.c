/*
 * Filename: testparseDB.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: tester for parseDB
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pa3.h"
#include "pa3Strings.h"
#include "test.h"

#define TEST_DICT_SMALL_NO_ERRORS "ref/small_dict1"
#define TEST_DICT_INVALID "invalid_dictionary_name"

#define REF_DB "ref/small_dict1_database.db"


static void testparseDB() {
  FILE *db;
  struct anagramInfo anagram;
   int i; 

  db = fopen(REF_DB, "r");

  parseDB(db, &anagram);

  for(i = 0; i < anagram.numOfAnagrams; i++) {
    printf("Word: %s\n HashKey: %d\n\n",
           anagram.anagramPtr[i].word, anagram.anagramPtr[i].hashKey);
  }
}

int main( void ) {
  (void) fprintf( stderr, "Starting testparseDB\n" );

  testparseDB();

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}


