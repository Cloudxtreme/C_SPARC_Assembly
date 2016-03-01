/*
 * filename: testfindUniq.c
 * author: TODO: enter your name
 * userid: TODO: enter your cs30x login id
 * description: tester for findUniq
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pa4.h"
#include "test.h"

#define IGNORE_CASE 0
#define NO_IGNORE_CASE 1

#define TEST_NO_ERROR 0
#define STR_ERR_BUILD_TEST_INPUT "Build test input fail.\n"

/*
 * Prototypes
 */
static void runTest(
    const char *testTitle,
    const char *testInputStr,
    int ignoreCase,
    const struct uniqInfo *refUniqInfo,
    const struct errorInfo *refErrorInfo
    );
static void compareResults(
    const struct uniqInfo *resUniqInfo,
    const struct uniqInfo *refUniqInfo,
    const struct errorInfo *resErrorInfo,
    const struct errorInfo *refErrorInfo
    );
static void buildTestInput(
    const char *testInputStr,
    struct parsedInputInfo *testInputInfoPtr
    );
static void freeTestInput(const struct parsedInputInfo *testInputInfoPtr); 
static void strnullcmp(const char *s1, const char *s2);

/*
 * TODO Function headers are always needed!
 */
static void testfindUniq( ) {
  /*
   * Name: Two Lines Match
   * Description: Input where there are two lines and both match.
   */
  char *TestTitleTwoLinesMatch = "Two Lines Match";
  char StringTwoLinesMatch[] = "hello\nhello\n"; 
  int IgnoreCaseTwoLinesMatch = NO_IGNORE_CASE;
  struct errorInfo ErrorInfoTwoLinesMatch = {ErrNone, ""};
  uniq_t UniqArrayTwoLinesMatch[] = {
    {2, "hello\n", "hello\n"}
  };
  struct uniqInfo UniqInfoTwoLinesMatch = {UniqArrayTwoLinesMatch, 1};

  runTest(
      TestTitleTwoLinesMatch,
      StringTwoLinesMatch, 
      IgnoreCaseTwoLinesMatch,
      &UniqInfoTwoLinesMatch, 
      &ErrorInfoTwoLinesMatch
      );
  /*
   * Name: Empty Input
   * Description: Empty input.
   */
  char *TestTileEmptyInput = "Empty Input";
  char StringEmptyInput[] = "";
  int IgnoreCaseEmptyInput = NO_IGNORE_CASE;
  struct errorInfo ErrorInfoEmptyInput = {ErrNone, ""};
  uniq_t *UniqArrayEmptyInput = NULL;
  struct uniqInfo UniqInfoEmptyInput = {UniqArrayEmptyInput, 0};

  runTest(
      TestTileEmptyInput,
      StringEmptyInput, 
      IgnoreCaseEmptyInput,
      &UniqInfoEmptyInput, 
      &ErrorInfoEmptyInput
      );


  /* TODO Come up with more test cases */
}

/*
 * TODO Function headers are always needed!
 */
int main( ) {
  (void) fprintf( stderr, "Starting testfindUniq\n" );

  testfindUniq();

  (void) fprintf(stderr, "Done.\n");

  return 0;
}

/*
 * Name: runTest()
 * Description: Run one test on findUniq() using given parameters.
 * Return: Zero on success; nonzero on failure
 */
static void runTest(
    const char *testTitle,
    const char *testInputStr,
    int ignoreCase,
    const struct uniqInfo *refUniqInfo,
    const struct errorInfo *refErrorInfo
    ) {
  fprintf(stdout, "\n=== %s ===\n", testTitle);

  // Initialize argInfo struct
  struct argInfo argInfo = {0};
  if (ignoreCase == IGNORE_CASE) {
    argInfo.options |= OPT_IGNORE_CASE;
  }

  // Build test input
  struct parsedInputInfo testInputInfo;
  buildTestInput(testInputStr, &testInputInfo);

  struct uniqInfo uniqInfo;
  struct errorInfo errorInfo;
  setErrorInfo(&errorInfo, ErrNone, NULL);
  findUniq(&testInputInfo, &argInfo, &uniqInfo, &errorInfo);

  compareResults(&uniqInfo, refUniqInfo, &errorInfo, refErrorInfo);

  freeTestInput(&testInputInfo);
}

/*
 * Name: compareResults()
 * Description: Compare result and reference structs uniqInfo and errorInfo.
 */
static void compareResults(
    const struct uniqInfo *resUniqInfo,
    const struct uniqInfo *refUniqInfo,
    const struct errorInfo *resErrorInfo,
    const struct errorInfo *refErrorInfo
    ) {
  // Compare errorInfo
  TEST(resErrorInfo->errorCode == refErrorInfo->errorCode);
  TEST(strncmp(resErrorInfo->errorMsg, 
        refErrorInfo->errorMsg, ERROR_MSG_SIZE) == 0);

  // compare uniqInfo
  int matchingNumOfEntries = 
    resUniqInfo->numOfEntries == refUniqInfo->numOfEntries;
  TEST(matchingNumOfEntries);

  // Check each entry
  if (matchingNumOfEntries) {
    int i;
    for (i = 0; i < refUniqInfo->numOfEntries; i++) {
      uniq_t refUniq = refUniqInfo->uniqPtr[i]; 
      uniq_t resUniq = resUniqInfo->uniqPtr[i]; 

      TEST(refUniq.count == resUniq.count);
      TEST(strcmp(refUniq.line, resUniq.line) == 0);
      strnullcmp(refUniq.dups, resUniq.dups);
    }
  }
}

/*
 * Name: buildTestInput()
 * Description: Build array of lines based on test input string.
 * Return: Zero on success; nonzero on failure
 */
static void buildTestInput(
    const char *testInputStr,
    struct parsedInputInfo *testInputInfoPtr
    ) {
  char *endLinePtr = NULL;
  const char *beginLinePtr = testInputStr;
  char **testInput = NULL;
  int numOfEntries = 0;

  // Add entry to test input array for each line of input string
  while( (endLinePtr = strchr(beginLinePtr, '\n')) != NULL) {
    *endLinePtr = '\0';

    // Expand array of lines
    testInput = realloc(testInput, (numOfEntries +1) * sizeof(char*));

    // Allocate memory for line
    char *line = calloc(strlen(beginLinePtr)+2, sizeof(char));

    /*
     * Copy string into line. 
     * Note: We do not need to add +1 to length because calloc() zero fills.
     */
    strncpy(line, beginLinePtr, strlen(beginLinePtr));

    // Add newline back
    line[strlen(beginLinePtr)] = '\n';

    testInput[numOfEntries++] = line;
    beginLinePtr = ++endLinePtr;
  }

  // Update values
  testInputInfoPtr->parsedInputPtr = testInput;
  testInputInfoPtr->numOfEntries = numOfEntries;
}

/*
 * Name: freeTestInput()
 * Description: Frees dynamic memory used for test input array.
 */
static void freeTestInput(const struct parsedInputInfo *testInputInfoPtr) {  
  // Free each line in array
  int i;
  for (i = 0; i < testInputInfoPtr->numOfEntries; i++) {
    free(testInputInfoPtr->parsedInputPtr[i]);
  }

  // Free array
  free(testInputInfoPtr->parsedInputPtr);
}

/*
 * Compare two strings, if either is NULL compare addresses.
 */
static void strnullcmp(const char *s1, const char *s2) {
  if (s1 == NULL || s2 == NULL) {
    TEST(s1 == s2);
  }
  else {
    TEST(strcmp(s1, s2) == 0);
  }
}
