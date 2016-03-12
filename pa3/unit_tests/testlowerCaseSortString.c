/*
 * Filename: testlowerCaseSortString.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: Tester for lowerCaseSortString
 */

#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h> // strlen, strncmp

#include "pa3.h"
#include "test.h"

/*
 * TODO Function headers are always needed!
 */
static void runTest(const char *word, const char *lowerCaseSorted) {
  int n = strlen(word)+1;
  char *buf = (char*) malloc(n); 

  lowerCaseSortString(word, n, buf);

  TEST(strncmp(lowerCaseSorted, buf, n) == 0);

  free(buf);
}

/*
 * TODO Function headers are always needed!
 */
static void testlowerCaseSortString() {
  char *word, *lowerCaseSorted;

  word = "Hello"; lowerCaseSorted = "ehllo";
  runTest(word, lowerCaseSorted);



  /* TODO Come up with more test cases */
}

/*
 * TODO Function headers are always needed!
 */
int main( void ) {
  (void) fprintf( stderr, "Starting testlowerCaseSortString\n" );

  testlowerCaseSortString( );

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}
