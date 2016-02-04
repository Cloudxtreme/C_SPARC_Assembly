/*
 * Filename: testconvertToBCD.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Unit test program to test the function convertToBCD().
 * Date: 2/3/2106
 * Sources of Help: These files were provided, just added more test cases 
 */ 

// First Library Header, then local ones
#include <stdio.h>
#include "pa2.h"
#include "test.h"

// Function prototype
void testconvertoBCD();

void testconvertToBCD() {

  long clockDecimal[3];
  unsigned char clockBCD[3];

  /* Test 1 */
  clockDecimal[HR_INDEX] = 12;
  clockDecimal[MIN_INDEX] = 34;
  clockDecimal[SEC_INDEX] = 56;

  convertToBCD(clockDecimal, clockBCD);

  TEST( (clockBCD[HR_INDEX] == 0x12) && (clockBCD[MIN_INDEX] == 0x34) &&
      (clockBCD[SEC_INDEX] == 0x56) );

  /* Test 2 */
  clockDecimal[HR_INDEX] = 0;
  clockDecimal[MIN_INDEX] = 0;
  clockDecimal[SEC_INDEX] = 0;

  convertToBCD(clockDecimal, clockBCD);

  TEST( (clockBCD[HR_INDEX] == 0x00) && (clockBCD[MIN_INDEX] == 0x00) &&
      (clockBCD[SEC_INDEX] == 0x00 ) );

  /* Test 3 */
  clockDecimal[HR_INDEX] = 23;
  clockDecimal[MIN_INDEX] = 59;
  clockDecimal[SEC_INDEX] = 59;

  convertToBCD(clockDecimal, clockBCD);

  TEST( (clockBCD[HR_INDEX] == 0x23) && (clockBCD[MIN_INDEX] == 0x59) &&
      (clockBCD[SEC_INDEX] == 0x59 ) );

}

int main( void ) {

  fprintf(stderr, "Running tests for convertToBCD...\n");
  testconvertToBCD();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
