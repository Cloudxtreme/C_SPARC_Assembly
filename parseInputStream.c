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
  //int i;                  // int to hold for-loop counter used to free mem
  
  while(fgets(buf, BUFSIZ, stream) != NULL)  {
    linesTmpPtr = (char **)realloc(linesTmpPtr, (sizeof(char *)*(lineCount+1)));
    
    if(linesTmpPtr != NULL) {
      line = (char *)calloc(strlen(buf)+1, sizeof(char));

      if(line != NULL) {
        strncpy(line, buf, strlen(buf)+1);
      } else {
        free(line);
        setErrorInfo(errorInfo, ErrErrno_M, STR_ERR_PARSE_INPUT);
        return -1;
      } 
      linesPtr = linesTmpPtr;
      linesPtr[lineCount] = line;
      lineCount++;
    } else {
      free(linesPtr);
      setErrorInfo(errorInfo, ErrErrno_M, STR_ERR_PARSE_INPUT);
      return -1;
    }
  }
  


  if((argInfoPtr->options & OPT_SORT_INPUT) == OPT_SORT_INPUT) {
    qsort(linesPtr, lineCount, sizeof(char *), sortInputCompare); 
  }
  
  parsedInputInfoPtr->parsedInputPtr = linesPtr;
  parsedInputInfoPtr->numOfEntries = lineCount;

  return 0;








}
