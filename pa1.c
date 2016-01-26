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
main( void ) {

  char x = 'Z';
  drawXOR( x, 3, 100000 );
  return 0;
}
