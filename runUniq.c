/*
 * Filename: runUniq.c  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Performs main fucntion of myuniq program by calling other 
 *              functions.
 * Date: 3/6/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function name: runUniq() 
 *
 * Function prototype: void runUniq( const struct argInfo *argInfoPtr,
 *                                   struct errorInfo *errorInfo );
 *
 * Description: Performs main function of myuniq program by calling other 
 *              functions. First opens inputFile and outputFile is specified,
 *              otherwise uses stdin and stdout. Then parses the inputFile or
 *              stdin with parseInputStream(). Then generates table of struct
 *              uniqs with findUniq(). Then write results to outputFile or 
 *              stdout by calling printResults(). Finally free memory and 
 *              close files if opened.
 *          
 * Parameters: 
 *      arg 1 - const struct argInfo *argInfoPtr -- struct argInfo
 *      arg 2 - struct errorInfo *errorInfoPtr
 *
 * Side Effects: Runs the myuniq program by calling other the other functions
 *               in this program such as parseInputStream, findUniq(), and 
 *               printResults().
 *              
 * Error Conditions: 
 *    If fopen() fails to open the file, in which case ErrErrno_M will be set
 *    and the errorMsg will be the failing file name. Will return in case of 
 *    failure.
 *
 *    If parseInputStream() fails, error will already be set by the 
 *    parseInputStream() function. Will return in case of failure.
 *
 *    If findUniq() fails, error wil already be set by the findUniq() function.
 *    Will return in case of failure. 
 *    
 *    In case of parseInputStream() and findUniq() errors, free the dynamically
 *    allocated memory before immediately returning.
 *
 * Return Value: None
 */

void
runUniq( const struct argInfo *argInfoPtr, struct errorInfo *errorInfoPtr ) {

  /* Local Variables */
  
  // struct to hold parsedInputInfo, will be passed to parseInputStream()
  struct parsedInputInfo parsedInputInfoPtr;

  // struct to hold uniqInfo, will be passed to findUniq()
  struct uniqInfo uniqInfoPtr;
  
  FILE *input = NULL;         // input file stream
  FILE *output = NULL;        // output file stream

  int errParseInput = 0;      // Holds return value from parseInputStream()
  int errFindUniq = 0;        // Holds return value from findUniq()

  int i;                      // loop-counter variable for free() in loops
  
  /* Check to see that inFile in argInfo is not NULL, if it is then set input
   * to be stdin, otherwise open inFile with FILE_READ_MODE and set the input
   * stream equal to it. If there is an error opening the file, then set 
   * errorInfo and return immediately. 
   */
  if(argInfoPtr->inFile == NULL) {
    input = stdin;
  } else {
    errno = 0;
    input = fopen(argInfoPtr->inFile, FILE_READ_MODE);
    if(errno != 0) {
      setErrorInfo(errorInfoPtr, ErrErrno_M, argInfoPtr->inFile);
      return;
    }
  }

  /* Check to see that OutFile in argInfo is not NULL, if it is then set output
   * to be stdout, otherwise open outFile with FILE_WRITE_MODE and set the 
   * output stream equal to it. If there is an error opening the file, then set 
   * errorInfo and return immediately. 
   */
  if(argInfoPtr->outFile == NULL) {
    output = stdout;
  } else {
    errno = 0;
    output = fopen(argInfoPtr->inFile, FILE_WRITE_MODE);
    if(errno != 0) {
      setErrorInfo(errorInfoPtr, ErrErrno_M, argInfoPtr->inFile);
      return;
    }
  }

  // Call parseInputStream() and set errParseInput equal to its return value
  errParseInput = parseInputStream(input, argInfoPtr, &parsedInputInfoPtr,
                                   errorInfoPtr );
  /* If errParseInput is nonzero, then free all the lines read in and return
   * immediately; errorInfo is already set in parseInputStream(). 
   */
  if(errParseInput != 0) {
    for(i = 0; i < parsedInputInfoPtr.numOfEntries; i++) {
      free(&parsedInputInfoPtr.parsedInputPtr[i]);
    }
    return;
  }
  
  // Call findUniq() and set errFindUniq equal to its return value
  errFindUniq = findUniq(&parsedInputInfoPtr, argInfoPtr, &uniqInfoPtr, 
                         errorInfoPtr);
  /* If errFindUniq is nonzero, then free all uniq struct elements in the 
   * uniqPtr array and return immediately; errorInfo is already set in 
   * parseInputStream(). 
   */
  if(errFindUniq != 0) {
    for(i = 0; i < uniqInfoPtr.numOfEntries; i++) {
      free(&uniqInfoPtr.uniqPtr[i]);
    }
    return;
  }

  // Call printResults() passing in output stream, argInfoptr, and uniqInfoPtr
  printResults(output, argInfoPtr, &uniqInfoPtr);
  
  // Free all the lines read in by parsedInputStream()
  for(i = 0; i < parsedInputInfoPtr.numOfEntries; i++) {
    free(&parsedInputInfoPtr.parsedInputPtr[i]);
  }

  // Free all the uniq struct elements created by findUniq()
  for(i = 0; i < uniqInfoPtr.numOfEntries; i++) {
    free(&uniqInfoPtr.uniqPtr[i]);
  }
   
  // Close the input and output stream 
  fclose(input);
  fclose(output);
}
