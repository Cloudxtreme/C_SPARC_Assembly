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
printResults( FILE *outstream, const struct argInfo *argInfoPtr,
              const struct uniqInfo *uniqInfoPtr ) {

  /* Local Variables */
  struct timeval tm;

  char time[BUFSIZ];
  
  int countFlag = 0;

  int duplicateEntries = 0;
  int uniqueEntries = 0;
  int totalEntries = 0;

  int duplicateLines = 0;
  int uniqueLines = 0;
  int totalLines = 0;

  int i;


  if((argInfoPtr->options & FLAG_SORT_OUTPUT) == FLAG_SORT_OUTPUT) {
    if((argInfoPtr->options & FLAG_COUNT) == FLAG_COUNT) {
      qsort(uniqInfoPtr->uniqPtr, uniqInfoPtr->numOfEntries, 
            sizeof(struct uniq), compareCount);
      countFlag = 1;
    } else {
      qsort(uniqInfoPtr->uniqPtr, uniqInfoPtr->numOfEntries, 
            sizeof(struct uniq), compareLine);
    }
  }
  
  for(i = 0; i < uniqInfoPtr->numOfEntries; i++) {
    switch(argInfoPtr->outputMode) {
      case DuplicateAll:
        if(uniqInfoPtr->uniqPtr[i].dups != NULL) {
          printf("%s", uniqInfoPtr->uniqPtr[i].dups);
        }
        break;

      case DuplicateOnly:
        if(uniqInfoPtr->uniqPtr[i].count > 1) {
          if(countFlag == 1) {
            printf("%d ", uniqInfoPtr->uniqPtr[i].count); 
            printf("%s", uniqInfoPtr->uniqPtr[i].line);
          } else {
            printf("%s", uniqInfoPtr->uniqPtr[i].line);
          }
        }
      break;

      case Unique:
        if(uniqInfoPtr->uniqPtr[i].count == 1) {
          if(countFlag == 1) {
            printf("%d ", uniqInfoPtr->uniqPtr[i].count); 
            printf("%s", uniqInfoPtr->uniqPtr[i].line);
          } else {
            printf("%s", uniqInfoPtr->uniqPtr[i].line);
          }
        }
        break;

      case Regular:
        if(countFlag == 1) {
          printf("%d ", uniqInfoPtr->uniqPtr[i].count); 
          printf("%s", uniqInfoPtr->uniqPtr[i].line);
        } else {
          printf("%s", uniqInfoPtr->uniqPtr[i].line);
        }
        break;
    }
    
    if(uniqInfoPtr->uniqPtr[i].count > 1) {
      duplicateEntries += 1;
      duplicateLines += uniqInfoPtr->uniqPtr[i].count;
    }

    uniqueLines = uniqInfoPtr->numOfEntries;
    if(uniqInfoPtr->uniqPtr[i].count == 1) {
      uniqueEntries += 1;
    }
   
    totalEntries = uniqueEntries + duplicateEntries;
    totalLines = uniqueLines + duplicateLines;
  }

  pa4gettimeofday(&tm, NULL);
  strftime(time, BUFSIZ, STR_TIME_FORMATER, localtime(&tm.tv_sec)); 
  



}

