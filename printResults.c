/*
 * Filename: printResults.c  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Prints the results obtained from running findUniq() and 
 *              depending on what flags were set in parseArgs() and stored in
 *              struct argInfo.
 * Date: 3/6/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>    // Needed for FILE
#include <stdlib.h>   // Needed for qsort()

#include "pa4.h"          // Always needed
#include "pa4Strings.h"   // Needed for strings

/*
 * Function name: printResults()
 *
 * Function prototype: 
 *    void printResults( FILE *outFile, 
 *                       const struct argInfo *argInfoPtr,
 *                       const struct uniqInfo *uniqInfoPtr );
 *
 * Description: Prints the results obtained after running findUniq() depending
 *              on what flags were set in parseArgs() and stored in struct 
 *              argInfo. Traverses the uniq_t array in uniqInfoPtr, printing
 *              out strings based on the flags that were parsed in. Prints out
 *              a summary if the -x flag was present.
 *          
 * Parameters: 
 *      arg 1 - FILE *outfile -- where the output will be printed
 *      arg 2 - const struct argInfo *argInfoPtr -- struct argInfo
 *      arg 3 - const struct uniqInfo *uniqInfoPtr -- struct uniqInfo        
 *
 * Side Effects: Prints out results from findUniq() depending on what flags 
 *               were parsed in.
 *              
 * Error Conditions: None
 *      
 * Return Value: None
 */

void 
printResults( FILE *outFile, const struct argInfo *argInfoPtr,
              const struct uniqInfo *uniqInfoPtr ) {

  /* Local Variables */
  struct timeval tm;          // timeval struct needed for pa4gettimeofday()

  char time[BUFSIZ];          // string to hold formatted time
  
  int countFlag = 0;          // boolean to check if count flag is present

  int duplicateEntries = 0;   // holds val for duplicate entries
  int uniqueEntries = 0;      // holds val for unique entries
  int totalEntries = 0;       // holds val for total entries

  int duplicateLines = 0;     // holds val for duplicate lines
  int uniqueLines = 0;        // holds val for unique lines
  int totalLines = 0;         // holds val for total lines

  int i;                      // for-loop counter

  // Check to see if sort output flag has ben set
  if((argInfoPtr->options & FLAG_SORT_OUTPUT) == FLAG_SORT_OUTPUT) {
    // If coutn flag has been set then qsort using compareCount, and set
    // count flag boolean
    if((argInfoPtr->options & FLAG_COUNT) == FLAG_COUNT) {
      qsort(uniqInfoPtr->uniqPtr, uniqInfoPtr->numOfEntries, 
            sizeof(struct uniq), compareCount);
      countFlag = 1;
    } else {
      // If coung flag has not  been set then always do qsort with compareLine
      qsort(uniqInfoPtr->uniqPtr, uniqInfoPtr->numOfEntries, 
            sizeof(struct uniq), compareLine);
    }
  }
  
  // Iterate through the uniq struct array
  for(i = 0; i < uniqInfoPtr->numOfEntries; i++) {
    // Use switch case to determine output mode set in argInfoPtr
    switch(argInfoPtr->outputMode) {
      // If mode is DuplicateAll, then print each uniq struct element's dups 
      // member in array, where dups member is != NULL
      case DuplicateAll:
        if(uniqInfoPtr->uniqPtr[i].dups != NULL) {
          (void) fprintf(outFile,"%s", uniqInfoPtr->uniqPtr[i].dups);
        }
        break;
      
      /* If mode is DuplicateOnly, then print each uniq struct element's line 
       * member in array, were the count member is greater than 1, if count 
       * flag boolean is set, then first print count also. 
       */
      case DuplicateOnly:
        if(uniqInfoPtr->uniqPtr[i].count > 1) {
          if(countFlag == 1) {
            (void) fprintf(outFile, "%d ", uniqInfoPtr->uniqPtr[i].count); 
            (void) fprintf(outFile, "%s", uniqInfoPtr->uniqPtr[i].line);
          } else {
            (void) fprintf(outFile, "%s", uniqInfoPtr->uniqPtr[i].line);
          }
        }
      break;
      
      /* If mode is Unique, then print each uniq struct element's line member 
       * in array, where the count member is eqaul to 1, if count flag boolean 
       * is set, then fist print count also.
       */
      case Unique:
        if(uniqInfoPtr->uniqPtr[i].count == 1) {
          if(countFlag == 1) {
            (void) fprintf(outFile, "%d ", uniqInfoPtr->uniqPtr[i].count); 
            (void) fprintf(outFile, "%s", uniqInfoPtr->uniqPtr[i].line);
          } else {
            (void) fprintf(outFile, "%s", uniqInfoPtr->uniqPtr[i].line);
          }
        }
        break;
      
      /* If mode is regular, then print all elements of uniq struct array's 
       * line member, if the count flag boolean is set, then first print the 
       * count member for each element also.
       */
      case Regular:
        if(countFlag == 1) {
          (void) fprintf(outFile, "%d ", uniqInfoPtr->uniqPtr[i].count); 
          (void) fprintf(outFile, "%s", uniqInfoPtr->uniqPtr[i].line);
        } else {
          (void) fprintf(outFile, "%s", uniqInfoPtr->uniqPtr[i].line);
        }
        break;
    }
    
    /* For each uniq struct array element where count member is greater than 1,
     * increment duplicateEntries, and add up all the count members to get
     * duplicateLines.
     */
    if(uniqInfoPtr->uniqPtr[i].count > 1) {
      duplicateEntries += 1;
      duplicateLines += uniqInfoPtr->uniqPtr[i].count;
    }
    
    /* uniqueLines is just equal to numOfEntries in uniqInfoPtr. For each uniq
     * struct array element where count is equal to one, increment 
     * uniqueEntries.
     */
    uniqueLines = uniqInfoPtr->numOfEntries;
    if(uniqInfoPtr->uniqPtr[i].count == 1) {
      uniqueEntries += 1;
    }
  }
  
  // totalEntries is just the sum of unique and duplicate entries
  totalEntries = uniqueEntries + duplicateEntries;

  // totalLines is just the sum of unique and duplicate lines
  totalLines = uniqueLines + duplicateLines;

  // get epoch time by calling pa4gettimeofday and passing in a struct timeval
  pa4gettimeofday(&tm, NULL);

  // format the time using localtime(), use strftime to store into string time
  strftime(time, BUFSIZ, STR_TIME_FORMATER, localtime(&tm.tv_sec)); 
  
  // If the summary flag has been set in argInfoPtr, then print summary
  if((argInfoPtr->options & FLAG_SUMMARY) == FLAG_SUMMARY) {
    (void) fprintf(outFile, STR_PRINT_SUMMARY, duplicateEntries, uniqueEntries,
                   totalEntries, duplicateLines, uniqueLines, totalLines, 
                   time);
   }
}

