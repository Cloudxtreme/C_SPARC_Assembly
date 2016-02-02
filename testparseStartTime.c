#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * TODO Function headers are always needed!
 */

void testparseStartTime() {
  long clockDecimal[3];

  TEST( parseStartTime( clockDecimal, "::" ) == 0 );
  TEST( clockDecimal[HR_INDEX] == 0 );
  TEST( clockDecimal[MIN_INDEX] == 0 );
  TEST( clockDecimal[SEC_INDEX] == 0 );

  /*
   * If there is an error being thrown, no need to check array values
   * For example... 12:50:aa - No need to check that 12 and 50 are properly
   * set in the clockDecimal array
   */

  TEST( parseStartTime(clockDecimal, ":::" ) == ERR_TIME_FORMAT );

  TEST( parseStartTime(clockDecimal, "a:a:a" ) ==
    (ERR_HR_VALUE | ERR_MIN_VALUE | ERR_SEC_VALUE) );

  /* TODO Come up with more test cases */
}

int main( void ) {

  fprintf(stderr, "Running tests for parseStartTime...\n");
  testparseStartTime();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}

