/*
 * Filename: pa1.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Driver for drawXOR functionality. main() resides in this file
 *              and will do all input argument checking, after their conversion
 *              from strings to long, and call the drawXOR function, passing in
 *              range checked arguments.
 * Date: 1/25/16
 * Sources of Help: PA1 Assignment Sheet, PA1 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Std C Lib header files first, then local headers.
 */

/* Local Headers */
#include "pa1.h"
#include "pa1Strings.h"

/*
 * Function name: main()
 * Function prototype: int main( int argc, char *argv[] );
 * Description: Main driver for drawing XOR patter, given input of
 *              XOR character, width of pattern, and speed. 
 *              Input argument validation will be done here before
 *              calling drawXOR function and passing its parameters.
 * Parameters:
 *      argv[0] -- name of compiled program
 *      argv[1] -- Decimal value of XOR character
 *      argv[2] -- Width of XOR pattern
 *      argv[3] -- Speed to print pattern
 * Side Effects: Given input argument validation passes, a XOR pattern
 *               will be drawn to stdout
 * Error Conditions: Wrong number of input arguments, or if they are out of 
 *                   range (refer to pa1.h for defined ranges for input
 *                   arguments
 * Return Value: EXIT_FAILURE indicating failed execution
 *               EXIT_SUCCESS indicating successful execution
 */

int
main( int argc, char *argv[]  ) {
  
  // Local main() variable defines
  int integer_failure = 0;
  
  long xorChar = 0;   // var to hold xorChar when converted from string
  long width = 0;     // var to hold width when converted from string
  long speed = 0;     // var to hold speed when converted from string
  
  char *testptr = NULL;

  /* Check to see number of arguments passed is equal to 4, otherwise print
  *  usage error message to stderr and exit program with failure
  */
  if ( argc != NUM_ARGV ) {
    (void) fprintf( stderr, USAGE );
    return EXIT_FAILURE;
  }
  
  /* Convert all argument to type long, setting their respective variables
  *  equal to them, then check to see if the original argument is an integer
  *  by checking testptr to see if it is null or not, otherwise print integer
  *  error message to stderr and exit program with failure
  */
  xorChar = strtol( argv[1], &testptr, BASE );
  if ( testptr != NULL ) {
    (void) fprintf( stderr, INT_ERR, argv[1] );
    integer_failure = 1;
    testptr = NULL;
  }

  width = strtol( argv[2], &testptr, BASE );
  if ( testptr != NULL ) {
    (void) fprintf( stderr, INT_ERR, argv[2] );
    integer_failure = 1;
    testptr = NULL;
  }

  speed = strtol( argv[3], &testptr, BASE );
  if ( testptr != NULL ) {
    (void) fprintf( stderr, INT_ERR, argv[3] );
    integer_failure = 1;
    testptr = NULL;
  }

  if ( integer_failure == 1) {
    return EXIT_FAILURE;
  }















  drawXOR( xorChar, width, speed );
  return EXIT_SUCCESS;
}
