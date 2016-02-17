/*
 * Filename: testhashString.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: tester for hashString
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"
#include "test.h"

/*
 * TODO Function headers are always needed!
 */
static void testhashString( ) {
  char *word;
  int hashKey;
  /* 
   * Note that these hash values are different than those that will be written
   * to the database for the given word. The hashKeys stored in the database
   * are created from the lower-cased and sorted version of the word.
   */
  word = "Hello"; hashKey = 270013707;
  TEST(hashString(word) == hashKey);

  word = "tops"; hashKey = 10030661;
  TEST(hashString(word) == hashKey);

  word = "\0"; hashKey = 7;
  TEST(hashString(word) == hashKey);

  printf("%d\n", hashString(word));

  /* TODO Come up with more test cases */
}

/*
 * TODO Function headers are always needed!
 */
int main( ) {
  (void) fprintf( stderr, "Starting testhashString\n" );

  testhashString( );

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}
