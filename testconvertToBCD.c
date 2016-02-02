#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * TODO Function headers are always needed!
 */

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

  /* TODO Come up with more test cases */

}

int main( void ) {

  fprintf(stderr, "Running tests for convertToBCD...\n");
  testconvertToBCD();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
