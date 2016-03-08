/*
 * Filename: parseInputStream.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Reads input (file or stdin) and dynamically creates an array of
 *              pointers to the line sof input
 * Date: 3/1/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.1
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function name: parseInputStream()
 *
 * Function prototype: 
 *  int parseInputStream( FILE *stream, const struct argInfo *argInfoPtr,
 *                        struct parsedInputInfo *parsedInputInfoPtr,
 *                        struct errorInfo *errorInfo );
 *
 * Description: Reads input (file or stdin) and dynamically creates an array
 *              of pointers to the lines of input. Read one line at a time from
 *              the input stream using fgets. Use realloc() to create/expand
 *              an array of pointers to hold each line. This array increases
 *              by 4 bytes (size of any pointer) each time. Then use calloc()
 *              to allocate space for the current line, but allocate enough 
 *              memory as long as line plus one (to account for '\0'). Then
 *              copy the line from the input stream into the newly allocated
 *              space. Then insert the pointer to the current line in the array
 *              of pointers.
 *          
 * Parameters: 
 *      arg 1 - FILE *stream -- input stream (file or stdin)
 *      arg 2 - const struct argInfo *argInfoPtr - ptr to struct argInfo
 *      arg 3 - struct parsedInputInfo *parsedInputInfoPtr -- ptr to 
 *              parsedInputInfo struct
 *      arg 4 - struct errorInfo *errorInfo -- ptr to struct errorInfo
 *
 * Side Effects: Stores pointers to each line read in, into an array, and in 
 *               each array element we have the pointer to the line string
 *              
 * Error Conditions: If realloc() or calloc() fails (returns null pointer)
 *      
 * Return Value: 
 *    0 - Successfull
 *   -1 - Error
 */

int 
parseInputStream( FILE *stream, const struct argInfo *argInfoPtr, 
                  struct parsedInputInfo *parsedInputInfoPtr,
                  struct errorInfo *errorInfo ) {
  
  /* Local Varaibles */
  char buf[BUFSIZ];    // string to hold line read from stream
  char *line = NULL;    // string to hold line, will be exapnded by calloc()
  char **linesPtr = NULL;    // array of char pointers to hold each line
  char **linesTmpPtr = NULL; // temp array of char pointers to hold each line

  int lineCount = 0;      // int to hold value of line count
 
  // read a line in from the stream and store into buf string
  while(fgets(buf, BUFSIZ, stream) != NULL)  {
    // dynamically grow the linesTmpPtr array by 4 bytes (sizeof ptr) each time
    linesTmpPtr = (char **)realloc(linesTmpPtr, (sizeof(char *)*(lineCount+1)));
    
    /* Check to see if realloc() failed (returns NULL ptr), if it did then
     * free all the elements in the array first, then free the array. If it 
     * didn't then continue.
     */
    if(linesTmpPtr != NULL) {
      // allocate enough memory for the string read in
      line = (char *)calloc(strlen(buf)+1, sizeof(char));
      /* Check to see if calloc() failed (returns NULL ptr), if it did then 
       * free the memory allocated thus far for the string. If it didn't, then
       * continue
       */
      if(line != NULL) {
        /* copy the string read in (buf) into the properly size allocated 
         * string line, add one to length of copy to account for the null 
         * character
         */
        (void) strncpy(line, buf, strlen(buf)+1);
      } else {
        // Since calloc() failed, free line and set errorInfo, then return -1
        free(line);
        int j;
        for(j=0; j < lineCount; j++) {
          free(linesPtr[j]);
        }
        free(linesPtr);
        setErrorInfo(errorInfo, ErrErrno_M, STR_ERR_PARSE_INPUT);
        return -1;
      } 
      // Assign the realloc()'ed temp line array ptr to linesPtr
      linesPtr = linesTmpPtr;
      // Store the copied read in line from buf+'\0' into the line ptr array
      // at the correct index (lineCount)
      linesPtr[lineCount] = line;
      // Increase the line count (# of lines read in)
      lineCount++;
    } else {
      // Since realloc() failed, free all the lines in the line array first
      // then free the line array, then finally set errorInfo and return -1
      free(linesTmpPtr);
      int i;
      for(i=0; i < lineCount; i++) {
        free(linesPtr[i]);
      }
      free(linesPtr);
      setErrorInfo(errorInfo, ErrErrno_M, STR_ERR_PARSE_INPUT);
      return -1;
    }
  }
  
  //  Check to see if the Sort Input flag was set in argInfo, if it was
  //  then qsort the line array using sortInputCompare as the comparator
  if((argInfoPtr->options & OPT_SORT_INPUT) == OPT_SORT_INPUT) {
    qsort(linesPtr, lineCount, sizeof(char *), sortInputCompare); 
  }
  
  // Since no errors by now, set the parsedInputInfo struct parameters
  // and then return 0 for success
  parsedInputInfoPtr->parsedInputPtr = linesPtr;
  parsedInputInfoPtr->numOfEntries = lineCount;

  return 0;
}
