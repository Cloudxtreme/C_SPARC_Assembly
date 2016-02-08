/*
 * Filename: displayBCDClock.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Prints out the BCD Interval clock given array of BCD values.
 * Date: 2/7/16
 * Sources of Help: PA2 Assignment Sheet, PA2 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>
#include "pa2.h"
#include "pa2Strings.h"

/*
 * Function name: displayBCDClock()
 *
 * Function prototype: void displayBCDClock( const unsigned char clockBCD[] );
 *
 * Description: Prints the BCD Interval clock by first printing the nibbles 
 *              of hours, mins, and seconds, in a column, then lastly printing
 *              the hexadecimal values of the clock.           
 * 
 * Parameters: 
 *      arg 1 - const unsigned char clockBCD[] - holds hex char bytes of clock 
 * 
 * Side Effects: Prints nibbles of BCD Interval clock using O's and .'s, 
 *               followed by hexadecimal value of clock
 *              
 * Error Conditions: None
 *      
 * Return Value: None
 */

void
displayBCDClock( const unsigned char clockBCD[] ) {

  // Define Local variables
  int i = 0;      // Used as counter in for loop

  /* Get the ones and tesns mask values from defines in pa2.h,
   * doing this since we will be changing the mask in the program.
   */
  int ones_mask = ONES_MSK;     
  int tens_mask = TENS_MSK;

  // Temp unsigned chars to values of clock
  unsigned char hours_tmp;
  unsigned char mins_tmp;
  unsigned char secs_tmp;
  
  /* Loop is for each row of clock */
  for( i; i < ROWS; i++ ) {
    /* Get tens place mask result of hours MSB, and check if it is 1 or 0,
     * then print the appropriate character, followed by printing a space
     */
    hours_tmp = clockBCD[HR_INDEX] & tens_mask;
    if( hours_tmp ) {
      printChar( ONE_CHAR );
    } else {
      printChar( ZERO_CHAR );
    }
    
    /* Get ones place mask result of hours MSB, and check if it is 1 or 0,
     * then print the appropriate character, followed by printing a space
     */
    hours_tmp = clockBCD[HR_INDEX] & ones_mask;
    if( hours_tmp ) {
      printChar( ONE_CHAR );
    } else {
      printChar( ZERO_CHAR );
    }
    printChar( SPACE );

    /* Get tens place mask result of mins MSB, and check if it is 1 or 0,
     * then print the appropriate character, followed by printing a space
     */
    mins_tmp = clockBCD[MIN_INDEX] & tens_mask;
    if( mins_tmp ) {
      printChar( ONE_CHAR );
    } else {
      printChar( ZERO_CHAR );
    }
    
    /* Get ones place mask result of mins MSB, and check if it is 1 or 0,
     * then print the appropriate character, followed by printing a space
     */
    mins_tmp = clockBCD[MIN_INDEX] & ones_mask;
    if( mins_tmp ) {
      printChar( ONE_CHAR );
    } else {
      printChar( ZERO_CHAR );
    }
    printChar( SPACE );

    /* Get tens place mask result of secs MSB, and check if it is 1 or 0,
     * then print the appropriate character, followed by printing a space
     */
    secs_tmp = clockBCD[SEC_INDEX] & tens_mask;
    if( secs_tmp ) {
      printChar( ONE_CHAR );
    } else {
      printChar( ZERO_CHAR );
    }
    
    /* Get ones place mask result of secs MSB, and check if it is 1 or 0,
     * then print the appropriate character, followed by printing a space
     */
    secs_tmp = clockBCD[SEC_INDEX] & ones_mask;
    if( secs_tmp ) {
      printChar( ONE_CHAR );
    } else {
      printChar( ZERO_CHAR );
    }
    printChar( SPACE );

    /* Now we will shift the mask 1 bit left to get next binary digit of
     * nibble, when we run thru this loop next time.
     */
    tens_mask = tens_mask >> 1;
    ones_mask = ones_mask >> 1;

    /* Print newline after each row */
    printChar( NEWLINE );
  }
  
  /* Print hexadecimal values of clockBCD */
  printf( STR_BCD_TIME, clockBCD[HR_INDEX] );
  printf( STR_BCD_TIME, clockBCD[MIN_INDEX] );
  printf( STR_BCD_TIME, clockBCD[SEC_INDEX] );
  printChar( NEWLINE );
}
