#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * TODO Function headers are always needed!
 */

void testupdateClockDecimalValue() {

  long clockDecimal[3];
  clockDecimal[HR_INDEX] = 12;
  clockDecimal[MIN_INDEX] = 40;
  clockDecimal[SEC_INDEX] = 50;

  TEST( updateClockDecimalValue(&clockDecimal[HR_INDEX], 13, MAX_HR) == 1 );
  TEST( (clockDecimal[HR_INDEX] == 1 ));

  TEST( updateClockDecimalValue(&clockDecimal[MIN_INDEX], 19, MAX_MINUTE) == 0 );
  TEST( (clockDecimal[MIN_INDEX] == 59 ));


  /* TODO Come up with more test cases */

  
  clockDecimal[HR_INDEX] = 12;
  clockDecimal[MIN_INDEX] = 40;
  clockDecimal[SEC_INDEX] = 50;

  TEST( updateClockDecimalValue(&clockDecimal[MIN_INDEX], 20, MAX_MINUTE) == 0 );
  TEST( (clockDecimal[MIN_INDEX] == 0 ));

  clockDecimal[HR_INDEX] = 0;
  clockDecimal[MIN_INDEX] = 0;
  clockDecimal[SEC_INDEX] = 35;

  TEST( updateClockDecimalValue(&clockDecimal[SEC_INDEX], 120, MAX_SEC) == 2 );
  TEST( (clockDecimal[SEC_INDEX] == 35 ));

  clockDecimal[HR_INDEX] = 12;
  clockDecimal[MIN_INDEX] = 40;
  clockDecimal[SEC_INDEX] = 50;

  TEST( updateClockDecimalValue(&clockDecimal[HR_INDEX], 20, MAX_HR) == 1 );
  TEST( (clockDecimal[HR_INDEX] == 8 ));


}

int main( void ) {

  fprintf(stderr, "Running tests for updateClockDecimalValue...\n");
  testupdateClockDecimalValue();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}

