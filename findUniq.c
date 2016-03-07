/*
 * Filename: findUniq.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Creates an array of struct uniqs (uniq_t) to hold info about
 *              string pared in
 * Date: 3/2/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.1
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function name: findUnit()
 *
 * Function prototype: 
 *  int findUniq( const struct parsedInputInfo *parsedInputInfoPtr,
 *                const struct argInfo *argInfo, 
 *                struct uniqInfo *uniqInfoPtr, 
 *                struct errorInfo *errorInfo );
 *
 * Description: Creates an array of struct uniqs (uniq_t) to hold info about 
 *              the strings parsed in. Loops through each line of input and
 *              creates an uniq_t entry in the array for each run of duplicates
 *              (each set of contiguous lines with matching strings). For the
 *              duplicate lines following the beginning of the run, increment
 *              the count of the uniq_t entry. The dups member of the uniq_t 
 *              entry is used for supporting the -D command line argument by
 *              expanding a dynimcally allocated array of chars to contain each
 *              duplicate line. 
 *          
 * Parameters: 
 *      arg 1 - const struct parsedInputInfo *parsedInputInfoPtr
 *      arg 2 - const struct argInfo *argInfo
 *      arg 3 - struct uniqInfo *uniqInfoPtr
 *      arg 4 - struct errorInfo *errorInfo
 *              
 * Side Effects: Populates members of uniqInfoPtr based on flags set in 
 *               argInfoPtr and the array of input lines stored in
 *               parsedInputInfoPtr.
 *              
 * Error Conditions: If realloc() fails and return null ptr 
 *      
 * Return Value: 
 *    0 - Success
 *   -1 - failure
 */

int
findUniq( const struct parsedInputInfo *parsedInputInfoPtr,
          const struct argInfo *argInfo,
          struct uniqInfo *uniqInfoPtr,
          struct errorInfo *errorInfo ) {
  
  /* Local Variables */

  // array of struct uniq, malloc so # of elements is 1 initally
  uniq_t *entries = malloc(sizeof(entries));

  // temp array of struct uniq, will use this one to expand
  uniq_t *entriesTmp = NULL;
  
  int i;          // for-loop counter variable 
  int size = 1;   // holds the val for size of array of struct uniq

  /* Check to see that parsedInputPtr is not NULL and we actally parsed stuff,
   * if not, then set uniqPtr to NULL and numOfEntries to 0, and return -1 for
   * failure. Othrwise continue.
   */
  if(parsedInputInfoPtr->parsedInputPtr != NULL) {
    // Initially set first struct uniq array element so its count is 1, dups is
    // NULL, and line is firest line parsed in 
    entries[0].count = 1;
    entries[0].dups = NULL;
    entries[0].line = parsedInputInfoPtr->parsedInputPtr[0];
    
    /* For each line read parsed in, compare it with last element in struct
     * uniq array.
     */
    for(i = 1; i < parsedInputInfoPtr->numOfEntries; i++) {
      char **tmp = parsedInputInfoPtr->parsedInputPtr;
      /* If ignore case option is set in argInfo, then use strIgnoreCaseCmp to
       * compare the line at ith element in parsedInputPtr with the last
       * elemnt in struct uniq array entries. Otherwise use strcmp to do 
       * comparison of lines.
       */
      if( (argInfo->options & OPT_IGNORE_CASE) == OPT_IGNORE_CASE) {
        /* Since lines were equal using strIgnoreCaseCmp(), we will add the 
         * line read in at the ith element of parsedInputPtr to the dups string
         * by first growing dups to accomodate size of new string plus 
         * whatever size was originally there. If realloc fails, then free all
         * the allocated memory, set errorInfo, and return -1 for failure
         */
        if((strIgnoreCaseCmp(entries[size-1].line, tmp[i], 
            strlen(tmp[i]))) == 0) {
          entries[size-1].count++;
          if(argInfo->outputMode == DuplicateAll) {
            char *dup = NULL;
            dup = (char *)realloc(dup, strlen(tmp[i]));
            if(dup != NULL) {
              strcpy(dup, tmp[i]);
              entries[size-1].dups = dup;
            } else {
              free(dup);
              setErrorInfo(errorInfo, ErrErrno_M, STR_ERR_FIND_UNIQ);
              return -1;
            }
          }
        } else {
          /* Since lines were not equal (when checking with strIgnoreCaseCmp())
           * grow the entriesTmp array, increase size, set entries equal to 
           * entriesTmp, then set newest element in struct uniq array (at 
           * element "size") so its line member is the ith line read in, its
           * count equal to 1 and dups equal to NULL.
           */
          entriesTmp = (struct uniq *)realloc(entriesTmp, 
                                              sizeof(struct uniq)*(size+1));
          size++;
          /* Check to see that realloc did not return NULL ptr, if it did then
           * free entries and entriesTmp, set errorInfo, and return -1 for 
           * failure
           */
          if(entriesTmp != NULL) {
            entries = entriesTmp;
            entries[size].line = tmp[i];
            entries[size].count = 1;
            entries[size].dups = NULL;
          } else {
            free(entries);
            free(entriesTmp);
            setErrorInfo(errorInfo, ErrErrno_M, STR_ERR_FIND_UNIQ); 
            return -1;
          }
        }
      } else {
        /* Since lines were equal using strcmp(), we will add the 
         * line read in at the ith element of parsedInputPtr to the dups string
         * by first growing dups to accomodate size of new string plus 
         * whatever size was originally there. If realloc fails, then free all
         * the allocated memory, set errorInfo, and return -1 for failure
         */
        if((strcmp(entries[size-1].line, tmp[i])) == 0) {
          entries[size-1].count++;
          if(argInfo->outputMode == DuplicateAll) {
            char *dup = NULL;
            dup = (char *)realloc(dup, strlen(tmp[i]));
            if(dup != NULL) {
              strcpy(dup, tmp[i]);
              entries[size-1].dups = dup;
            } else {
              free(dup);
              setErrorInfo(errorInfo, ErrErrno_M, STR_ERR_FIND_UNIQ);
              return -1;
            }
          }
        } else {
          /* Since lines were not equal (when checking with strcmp())
           * grow the entriesTmp array, increase size, set entries equal to 
           * entriesTmp, then set newest element in struct uniq array (at 
           * element "size") so its line member is the ith line read in, its
           * count equal to 1 and dups equal to NULL.
           */
          entriesTmp = (struct uniq *)realloc(entriesTmp, 
                                              sizeof(struct uniq)*(size+1));
          size++;
          /* Check to see that realloc did not return NULL ptr, if it did then
           * free entries and entriesTmp, set errorInfo, and return -1 for 
           * failure
           */
          if(entriesTmp != NULL) {
            entries = entriesTmp;
            entries[size].line = tmp[i];
            entries[size].count = 1;
            entries[size].dups = NULL;
          } else {
            free(entries);
            free(entriesTmp);
            setErrorInfo(errorInfo, ErrErrno_M, STR_ERR_FIND_UNIQ); 
            return -1;
          }
        }
      }
    }

  } else {
    /* If nothing was parsed in from parseInputStream(), then set uniqPtr to be 
     * NULL, and numOfEntries to 0 of uniqInfoPtr struct.
     */
    uniqInfoPtr->uniqPtr = NULL;
    uniqInfoPtr->numOfEntries = 0;
    return -1;
  }

  /* Since we had no errors this far, set uniqPtr equal to entries and
   * numOfEntries to size of the uniqInfoPtr struct
   */
  uniqInfoPtr->uniqPtr = entries;
  uniqInfoPtr->numOfEntries = size;
  
  // Free the entries uniq struct array
  free(entries);

  // Return 0 for success
  return 0;
}

