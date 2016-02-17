/*
 * Filename: testwriteAnagramToDB.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: tester for writeAnagramToDB
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "pa3.h"
#include "test.h"

#define TEMP_FILE "testWriteAnagramToDB_tmpfile"

#define FILE_TEST_WRITE_MODE "wb+"

/*
 * TODO Function headers are always needed!
 */
static void runTest(char *word, int hashKey, FILE *s) {
  struct anagram a;
  char buf[BUFSIZ];

  /* Reset file pointer for writing */
  rewind(s);

  /* Write to database */
  a.word = word;
  a.hashKey = hashKey;
  writeAnagramToDB(&a, s);

  /* Reset file pointer for reading */
  rewind(s);

  /* Read in word and haskKey from file */
  fgets(buf, BUFSIZ, s);
  TEST(strcmp(word, buf) == 0);

  /* Get end of word */
  char *endOfWord = strchr(buf, '\0');

  /* Ensure that endOfWord is found */
  if (endOfWord == NULL) {
    TEST(endOfWord != NULL);
  }
  else {
    TEST(strcmp(buf, word) == 0);
    TEST(memcmp(endOfWord+1, &hashKey, sizeof(hashKey)) == 0);
  }
}

/*
 * TODO Function headers are always needed!
 */
static void testwriteAnagramToDB( ) {
  char *word;
  int hashKey;
  
  /* Open file */
  FILE *ofp = fopen(TEMP_FILE, FILE_TEST_WRITE_MODE);

  word = "Hello"; hashKey = 123;
  runTest(word, hashKey, ofp);

  /* Delete temp file */
  unlink(TEMP_FILE);

  /* TODO Come up with more test cases */
}

/*
 * TODO Function headers are always needed!
 */
int main( ) {
  (void) fprintf( stderr, "Starting testwriteAnagramToDB\n" );

  testwriteAnagramToDB();

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}
