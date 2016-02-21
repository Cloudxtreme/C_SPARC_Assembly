/*
 * Filename: testcreateAngram.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: Tester for createAngram
 */

#include <stdio.h>
#include <stdlib.h> // free
#include <string.h> // strlen, strncmp

#include "pa3.h"
#include "test.h"

/*
 * TODO Function headers are always needed!
 */
static void runTest(const char *word) {
  struct anagram a;
  int n = strlen(word)+1;
  char *buf = malloc(n);

  lowerCaseSortString(word, n, buf);
  int hashKey = hashString(buf);

  createAnagram(word, &a);

  TEST(strncmp(a.word, word, n) == 0);
  TEST(a.hashKey == hashKey);

  free(a.word);
  free(buf);
}

/*
 * TODO Function headers are always needed!
 */
static void testcreateAnagram() {
  char *word;

  word = "Hello";
  runTest(word);

  /* TODO Come up with more test cases */
}

/*
 * TODO Function headers are always needed!
 */
int main( void ) {
  (void) fprintf( stderr, "Starting testcreateAnagram\n" );

  testcreateAnagram( );

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}
