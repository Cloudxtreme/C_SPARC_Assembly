/*
 * Filename: testparseArgs.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: tester for parseArgs
 */

#include <stdio.h>
#include <strings.h>
#include <getopt.h>

#include  "pa4.h"
#include  "test.h"

#define IGNORED 0

/*
 * Prototypes
 */
static void runTest(
    const char *testTitle,
    int argc,
    char *argv[],
    const struct argInfo *refArgInfo,
    const struct errorInfo *refErrorInfo
    );

static void strnullcmp(const char *s1, const char *s2);

/*
 * TODO Function headers are always needed!
 */
static void testparseArgs() {
  /*
   * Test: Many Flags No Files
   * Description: Using numerous flags without in/out file.
   */
  char *TestTitleManyFlagsNoFiles = "Many Flags No Files";
  char *ArgvManyFlagsNoFiles[] = {"./myuniq", "-dcisSx"};
  int ArgcManyFlagsNoFiles = 2;
  struct argInfo ArgInfoManyFlagsNoFiles = {
    OPT_COUNT | OPT_IGNORE_CASE | OPT_SORT_OUTPUT | OPT_SORT_INPUT | OPT_SUMMARY,
    DuplicateOnly, 
    NULL, 
    NULL
  };
  struct errorInfo ErrorInfoManyFlagsNoFiles = {ErrNone, ""};

  runTest(
      TestTitleManyFlagsNoFiles,
      ArgcManyFlagsNoFiles, 
      ArgvManyFlagsNoFiles, 
      &ArgInfoManyFlagsNoFiles,
      &ErrorInfoManyFlagsNoFiles
      );

  /*
   * Test: Mutual Exclusion
   * Descriptoin: Using two flags that are mutually exclusive.
   */
  char *TestTitleMutualExclusion = "Mutual Exclusion";
  char *ArgvMutualExclusion[] = {"./myuniq", "-d", "-D"};
  int ArgcMutualExclusion = 3;
  struct argInfo ArgInfoMutualExclusion = {
    IGNORED,
    IGNORED,
    (char *)IGNORED,
    (char *)IGNORED
  };
  struct errorInfo ErrorInfoMutualExclusion = {ErrMutualExcl, ""};

  runTest(
      TestTitleMutualExclusion,
      ArgcMutualExclusion,
      ArgvMutualExclusion,
      &ArgInfoMutualExclusion,
      &ErrorInfoMutualExclusion
      );

   /*
   * Test: Many Invalid No Files
   * Description: Using numerous flags with invalid flag  without in/out file.
   */
  char *TestTitleInvalidFlagNoFiles = "Invalid Flag";
  char *ArgvInvalidFlagsNoFiles[] = {"./myuniq", "-dcisSxT"};
  int ArgcInvalidFlagsNoFiles = 2;
  struct argInfo ArgInfoInvalidFlagsNoFiles = {
    OPT_COUNT | OPT_IGNORE_CASE | OPT_SORT_OUTPUT | OPT_SORT_INPUT | OPT_SUMMARY,
    DuplicateOnly, 
    NULL, 
    NULL
  };
  struct errorInfo ErrorInfoInvalidFlagsNoFiles = {ErrInvFlag, ""};

  runTest(
      TestTitleInvalidFlagNoFiles,
      ArgcInvalidFlagsNoFiles,
      ArgvInvalidFlagsNoFiles,
      &ArgInfoInvalidFlagsNoFiles,
      &ErrorInfoInvalidFlagsNoFiles
      );
  
   /*
   * Test: Many Valid with Files
   * Description: Using numerous flags with invalid flag  without in/out file.
   */
  char *TestTitleValidFlagsWithFiles = "Valid Flags with Files";
  char *ArgvFlagsWithFiles[] = {"./myuniq", "-dcisSx","ref/In1", "ref/Out1" };
  int ArgcValidFlagsWithFiles = 4;
  struct argInfo ArgInfoValidFlagsWithFiles = {
    OPT_COUNT | OPT_IGNORE_CASE | OPT_SORT_OUTPUT | OPT_SORT_INPUT | OPT_SUMMARY,
    DuplicateOnly, 
    "ref/In1", 
    "ref/Out1"
  };
  struct errorInfo ErrorInfoValidFlagsWithFiles = {ErrNone, ""};

  runTest(
      TestTitleValidFlagsWithFiles,
      ArgcValidFlagsWithFiles,
      ArgvFlagsWithFiles,
      &ArgInfoValidFlagsWithFiles,
      &ErrorInfoValidFlagsWithFiles
      );



}

/*
 * TODO Function headers are always needed!
 */
int main() {
  (void) fprintf( stderr, "Starting testparseArgs\n" );

  testparseArgs();

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}

/*
 * Name: runTest()
 * Description: Run one test on parseArgs() using given parameters.
 * Return: None
 */
static void runTest(
    const char *testTitle,
    int argc,
    char *argv[],
    const struct argInfo *refArgInfo,
    const struct errorInfo *refErrorInfo
    ) {
  fprintf(stdout, "\n=== %s ===\n", testTitle);

  // Parse args
  struct argInfo resArgInfo;
  struct errorInfo resErrorInfo;
  setErrorInfo(&resErrorInfo, ErrNone, NULL);
  parseArgs(argc, argv, &resArgInfo, &resErrorInfo);

  // Compare errorInfo
  TEST(resErrorInfo.errorCode == refErrorInfo->errorCode);
  TEST(strncmp(resErrorInfo.errorMsg, 
        refErrorInfo->errorMsg, ERROR_MSG_SIZE) == 0);

  // If no errors, compare argInfo
  if (resErrorInfo.errorCode == ErrNone && refErrorInfo->errorCode == ErrNone) {
    TEST(resArgInfo.options == refArgInfo->options);
    TEST(resArgInfo.outputMode == refArgInfo->outputMode);
    strnullcmp(resArgInfo.inFile, refArgInfo->inFile);
    strnullcmp(resArgInfo.outFile, refArgInfo->outFile);
  }

  // reset getopt
  optind = 0;
}

static void strnullcmp(const char *s1, const char *s2) {
  if (s1 == NULL || s2 == NULL) {
    TEST(s1 == s2);
  }
  else {
    TEST(strcmp(s1, s2) == 0);
  }
}
