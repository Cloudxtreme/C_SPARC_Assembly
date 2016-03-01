/*
 * filename: testparseInputStream.c
 * author: TODO: enter your name
 * userid: TODO: enter your cs30x login id
 * description: tester for parseInputStream
 */

#include  <stdio.h>
#include  <stdlib.h>
#include  <strings.h>

#include  "pa4.h"
#include  "test.h"

#define SYSRUN(CMD) (system(CMD))

static int countLines(FILE *);
static int compareFiles(char *, char *);
static void writeParsedInputToFile(struct parsedInputInfo *, FILE *);
static void sortFile(char *, char *);
static void removeFile(char *);
static void freeParsedInput(char **parsedInputPtr, int numOfEntries);

/*
 * Name: runTest()
 * Description: Run one test on parseInputStream().
 * 
 * Note: This does not support testing stdin as inFileStream.
 *
 * Return: None.
 */
static void runTest(struct argInfo * myArgInfo)
{
  FILE * inFileStream;
  FILE * tempFile;
  struct parsedInputInfo myParsedInputInfo;
  struct errorInfo myErrorInfo;
  char * filename = myArgInfo->inFile;
  int sorted = (myArgInfo->options & OPT_SORT_INPUT) != 0;

  fprintf(stdout, "\n=== %s Sorted (%d) ===\n", filename, sorted);

  //build parsedInputInfo struct
  inFileStream = fopen( filename, FILE_READ_MODE );
  (void) parseInputStream(inFileStream,  
                          myArgInfo, 
                          &myParsedInputInfo, 
                          &myErrorInfo );

  //write parsedInput to file
  char tempFilename[BUFSIZ];
  (void) snprintf( tempFilename, 
                   BUFSIZ, 
                   "%s_temporary",
                   filename );
  tempFile = fopen( tempFilename, FILE_WRITE_MODE );
  (void) writeParsedInputToFile( &myParsedInputInfo, tempFile );
  (void) fclose( tempFile );

  //sort file if flag set
  char sortedFilename[BUFSIZ];
  (void) snprintf( sortedFilename,
                   BUFSIZ,
                   "%s_sorted",
                   filename );
   
  //test numOfEntries
  TEST( countLines( inFileStream ) == myParsedInputInfo.numOfEntries );
  
  //compare generated file with proper output
  if( myArgInfo->options & OPT_SORT_INPUT ) {
    sortFile( filename, sortedFilename );
    TEST( compareFiles( tempFilename, sortedFilename ) == 0 );
  } else {
    TEST( compareFiles( tempFilename, filename ) == 0 );
  }

  //close file
  (void) fclose( inFileStream );

  //remove temporary file(s)
  if( myArgInfo->options & OPT_SORT_INPUT )
    removeFile( sortedFilename ); 
  removeFile( tempFilename );
  
  //free allocated memory
  freeParsedInput( myParsedInputInfo.parsedInputPtr,
                   myParsedInputInfo.numOfEntries );
}

static void testparseInputStream() {
  char * filename1 = "ref/uniq.test";
  struct argInfo myArgInfo1 = {0, Regular, filename1, NULL};
  runTest(&myArgInfo1);

  struct argInfo myArgInfo2 = {OPT_SORT_INPUT, Regular, filename1, NULL};
  runTest(&myArgInfo2);

  /* TODO Come up with more test cases */
}

int main() 
{
  (void) fprintf( stderr, "Starting testparseInputStream\n" );

  testparseInputStream();

  (void) fprintf( stderr, "Done.\n" );

  return 0;

}

/* rm a file */
static void removeFile(char * filename)
{
  char rmString[BUFSIZ];
  (void) snprintf( rmString, BUFSIZ, "rm %s", filename);
  (void) system( rmString );
}

/* create output file with sorted contents of specified input file */
static void sortFile(char * inFilename, char * outFilename) {
  char sortStr[BUFSIZ];
  (void) snprintf( sortStr, BUFSIZ, "sort %s -o %s", inFilename, outFilename);
  (void) system(sortStr);
}

/* Write parsed input to specified output */
static void writeParsedInputToFile(struct parsedInputInfo * parsedInputInfoPtr,
                                                                    FILE * out)
{
  int i;
  for(i = 0; i < parsedInputInfoPtr->numOfEntries; ++i) {
    (void) fprintf(out, "%s", parsedInputInfoPtr->parsedInputPtr[i]);
  }
}

/* Compare two files, returns 0 if identical */
static int compareFiles(char * filename1, char * filename2)
{
  char diffStr[BUFSIZ];
  (void) snprintf( diffStr, 
                   BUFSIZ, 
                   "diff %s %s &> /dev/null",
                   filename1, 
                   filename2);
  return system(diffStr);
}

/* Count the number of lines in a file */
static int countLines(FILE * fp) 
{
  /* seek to the beginning of the file */
  (void) fseek(fp, 0L, SEEK_SET);
  int lines = 0;;
  char ch;

  while( (ch = fgetc(fp)) != EOF) {
    if(ch == '\n')
      lines++;
  }
  
  return lines;
}

/* free dynamically allocated parsed input */
static void freeParsedInput(char **parsedInputPtr, int numOfEntries)
{
  int i;
  for( i = 0; i < numOfEntries; ++i) {
    free(parsedInputPtr[i]);
  }

  free(parsedInputPtr);
}
