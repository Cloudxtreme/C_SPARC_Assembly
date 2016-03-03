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
find uniq( const struct parsedInputInfoPtr *parsed,
           const struct argInfo *argInfo,
           struct uniqInfo *uniqInfoPtr,
           struct errorInfo *errorInfo ) {
  







  return 0;
}

