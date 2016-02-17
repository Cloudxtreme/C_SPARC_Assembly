/*
 * Filename: testsetupDB.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: tester for setupDB
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pa3.h"
#include "pa3Strings.h"
#include "test.h"

#define TEST_DICT_SMALL_NO_ERRORS "ref/small_dict1"
#define TEST_DICT_INVALID "invalid_dictionary_name"

#define REF_DB_SMALL_NO_ERRORS "ref/small_dict1_database.db"

#define PRINT_DB 1

/*
 * Function Prototypes
 */
static int compareDB(const char *db1Name, const char *db2Name, int printDB);
static int readFromDB(FILE *db, int isOpen, int printDB, char *buf, int *key);

/*
 * TODO Function headers are always needed!
 */
static void runTest(const char *srcDict, const char *destDB, const char *refDB, 
    const struct errorInfo *eiTest) {
  struct argInfo ai = {0};
  struct errorInfo ei;

  ai.dictFilename = srcDict;
  ai.anagramDB = destDB;

  setupDB(&ai, &ei);

  // Check the errors (or lack thereof)
  TEST(eiTest->errorCode == ei.errorCode);
  TEST(strncmp(eiTest->errorMsg, ei.errorMsg, ERROR_MSG_SIZE) == 0);

  // Check the contents of the database against a reference solution
  int retVal = compareDB(destDB, refDB, PRINT_DB);

  TEST(retVal == 0);
}

/*
 * TODO Function headers are always needed!
 */
static void testsetupDB( ) {
  struct errorInfo eiTest;
  char *srcDict, *destDB, *refDB;

  srcDict = TEST_DICT_SMALL_NO_ERRORS;
  destDB = STR_DEF_ANAGRAM_DB;
  refDB = REF_DB_SMALL_NO_ERRORS;
  setErrorInfo(&eiTest, ERR_NONE, NULL);
  runTest(srcDict, destDB, refDB, &eiTest);

  /* Try running on larger dictionaries */
}

/*
 * TODO Function headers are always needed!
 */
int main( ) {
  (void) fprintf( stderr, "Starting testsetupDB\n" );

  testsetupDB( );

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}

/*
 * Function: readFromDB
 * Description: Reads a word from the database if it is open.
 * Return: zero if nothing read, positive if no errors, negative if errors.
 */
static int readFromDB(FILE *db, int isOpen, int printDB, char *buf, int *key) {
  char *endOfWord;
  char localBuf[BUFSIZ];

  if (isOpen == 0) {
    return 0;
  }

  /* Read from database if opened */
  if (fgets(localBuf, BUFSIZ, db) == NULL) {
    return 0;
  }

  /* Get end of the struct anagram word */
  endOfWord = strchr(localBuf, '\0');

  /* Ensure that nul-terminating character was found */
  if (endOfWord == NULL) {
    return -1;
  }

  /* Copy word */
  (void) strcpy(buf, localBuf);

  /* Copy key */
  (void) memcpy(key, endOfWord+1, sizeof(*key));

  /* Print entry */
  if (printDB) {
    (void) printf("(%s, %d)", buf, *key);
  }

  return 1;
}

/*
 * Function: compareDB
 * Description: Compare two database files.
 * Return: non-zero if error, zero otherwise
 */
static int compareDB(const char *db1Name, const char *db2Name, int printDB) {
  FILE *db1fp = NULL;
  FILE *db2fp = NULL;
  char buf1[BUFSIZ], buf2[BUFSIZ];
  int db1Open = 0, db2Open = 0;

  /* Open database1 if not null */
  if (db1Name != NULL) {
    if ((db1fp = fopen(db1Name, FILE_READ_MODE)) == NULL) {
      return 1;
    }
    db1Open = 1;
  }

  /* Open database2 if not null */
  if (db2Name != NULL) {
    if ((db2fp = fopen(db2Name, FILE_READ_MODE)) == NULL) {
      if (db1Open) { (void) fclose(db1fp); }
      return 1;
    }
    db2Open = 1;
  }

  /* Compare both databases line by line */
  int db1RetVal = 1, db2RetVal = 1;
  int db1hashKey, db2hashKey;
  while (db1RetVal != 0 && db2RetVal != 0) {
    /* Read from database1 if open */
    if(printDB) { printf("\n"); }
    db1RetVal = readFromDB(db1fp, db1Open, printDB, buf1, &db1hashKey);

    /* Read from database2 if open */
    db2RetVal = readFromDB(db2fp, db2Open, printDB, buf2, &db2hashKey);
    if(printDB) { printf("\n"); }

    /* If either negative, error encountered */
    if (db1RetVal < 0 || db2RetVal < 0) {
      return 1;
    }

    /* If both open, ensure they match */
    if (db1Open && db2Open) {
      TEST(db1RetVal == db2RetVal);
      TEST(strcmp(buf1, buf2) == 0);
      TEST(db1hashKey == db2hashKey);
    }
  }

  /* Close any open file descriptors */
  if (db1Open) { (void) fclose(db1fp); }
  if (db2Open) { (void) fclose(db2fp); }

  return 0;
}

