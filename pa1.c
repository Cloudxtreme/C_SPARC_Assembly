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
 *                  Alicia Chen (Lab TA): helped me strtol pointer error
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
  int strtol_fail = 0;          // boolean for strtol fail
  int xorChar_range_fail = 1;   // boolean for xorChar range fail
  int width_range_fail = 1;     // boolean for width range fail
  int speed_range_fail = 1;     // boolean for speed range fail
  int width_odd_fail = 1;       // boolean for width odd fail
  
  long xorChar = 0;   // var to hold xorChar when converted from string
  long width = 0;     // var to hold width when converted from string
  long speed = 0;     // var to hold speed when converted from string
  
  char *testptr = NULL;   // test pointer used when doing strtol conversion

  /* Check to see number of arguments passed is equal to 4, otherwise print
  *  usage error message to stderr and exit program with failure
  */
  if ( argc != NUM_ARGV ) {
    (void) fprintf( stderr, USAGE );
    return EXIT_FAILURE;
  }

  /* Convert 1st argument string into long and set xorChar equal to it,
   * and check to see if argument was an integer by inspecting testptr,
   * otherwise print integer error. Then use checkRange assembly function 
   * to see if xorChar is within range, otherwise print the range error,
   * and set xorChar range boolean appropriately. 
   */
  xorChar = strtol( argv[1], &testptr, BASE );
  if ( *testptr == NULL ) {
    xorChar_range_fail = checkRange( MIN_XOR_CHAR, OFFSET_XOR_CHAR, xorChar );
    if (xorChar_range_fail == 0 || xorChar_range_fail == -1 ) {
      (void) fprintf( stderr, XOR_ERR, xorChar, MIN_XOR_CHAR, 
      MIN_XOR_CHAR+OFFSET_XOR_CHAR );
    }
  }
  else {
    (void) fprintf( stderr, INT_ERR, argv[1] );
    strtol_fail = 1;
    *testptr = NULL;
  }

  /* Convert 2nd argument string into long and set width equal to it, and
   * check to see if argument was an integer by inspecting testptr, 
   * otherwise print integer error. Then use checkRange assembly function
   * to see if width is within range, otherwise print range error, and
   * set width range boolean appropriately. Then also check to see if,
   * width is odd by calling isOdd assembly function, otherwise print
   * width odd error and set width odd boolean appropriately.
   */
  width = strtol( argv[2], &testptr, BASE );
  if ( *testptr == NULL ) { 
    width_range_fail = checkRange( MIN_WIDTH, OFFSET_WIDTH, width );
    if ( width_range_fail == 1 ) { 
      width_odd_fail = isOdd( width );
      if ( width_odd_fail == 0 ) {
        (void) fprintf( stderr, WIDTH_ODD_ERR, width );
      }
    }
    else { 
       (void) fprintf( stderr, WIDTH_ERR, width, MIN_WIDTH,
       MIN_WIDTH+OFFSET_WIDTH );
    }
  }  
  else {
    (void) fprintf( stderr, INT_ERR, argv[2] );
    strtol_fail = 1;
    *testptr = NULL;
  }

  /* Convert 3rd argument string into long and set speed equal to it, and
   * check to see if argument was an integer by inspecting testptr, 
   * otherwise print integer error. Then use checkRange assembly function
   * to see if speed is within range, otherwise print range error, and
   * set speed range boolean appropriately.
   */
  speed = strtol( argv[3], &testptr, BASE );
  if ( *testptr == NULL ) {
    speed_range_fail = checkRange( MIN_SPEED, OFFSET_SPEED, speed );
    if ( speed_range_fail == 0 || speed_range_fail == -1 ) {
      (void) fprintf( stderr, SPEED_ERR, speed, MIN_SPEED, 
      MIN_SPEED+OFFSET_SPEED );
    }
  }
  else {
    (void) fprintf( stderr, INT_ERR, argv[3] );
    strtol_fail = 1;
    *testptr = NULL;
  }

  // Check strtol failure boolean to exit program with failure or not
  if ( strtol_fail == 1) {
    return EXIT_FAILURE;
  }
  
  // Check range failure booleans to exit program with failure or not
  if ( xorChar_range_fail == 0 || xorChar_range_fail == -1 ) {
    return EXIT_FAILURE;
  }

  if ( width_range_fail == 0 || width_range_fail == -1 ) {
    return EXIT_FAILURE;
  }

  if ( speed_range_fail == 0 || speed_range_fail == -1 ) {
    return EXIT_FAILURE;
  }

  // Check width odd failure boolean to exit program with failure or not
  if ( width_odd_fail == 0 ) {
    return EXIT_FAILURE;
  }

  // Since no errors were encountered by now, draw the XOR pattern
  // by calling drawXOR assembly function.
  drawXOR( xorChar, width, speed );

  // Exit program with sucesss!!!! Hooray! Yippee!
  return EXIT_SUCCESS;
}
