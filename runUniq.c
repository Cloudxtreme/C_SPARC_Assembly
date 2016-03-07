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
 * Return Value: None
 */


