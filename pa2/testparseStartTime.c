/*
 * Filename: testparseStartTime.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Unit test program to test the function parseStartTime().
 * Date: 2/3/2106
 * Sources of Help: These files were provided, just added more test cases 
 */ 

// First Library Includes, then local ones
#include <stdio.h>
#include "pa2.h"
#include "test.h"

// Function prototype
void testparseStartTime();

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

  TEST( parseStartTime(clockDecimal, "a:a:a" ) ==
    (ERR_HR_VALUE | ERR_MIN_VALUE | ERR_SEC_VALUE) );

  TEST( parseStartTime( clockDecimal, "12:34:56" ) == 0 );
  TEST( clockDecimal[HR_INDEX] == 12 );
  TEST( clockDecimal[MIN_INDEX] == 34 );
  TEST( clockDecimal[SEC_INDEX] == 56 );

  TEST( parseStartTime( clockDecimal, "aa:34:56" ) == ERR_HR_VALUE );
  TEST( parseStartTime( clockDecimal, "12:aa:56" ) == ERR_MIN_VALUE );
  TEST( parseStartTime( clockDecimal, "12:50:aa" ) == ERR_SEC_VALUE );

  TEST( parseStartTime( clockDecimal, "25:34:56" ) == ERR_HR_RANGE );
  TEST( parseStartTime( clockDecimal, "12:60:56" ) == ERR_MIN_RANGE );
  TEST( parseStartTime( clockDecimal, "12:50:60" ) == ERR_SEC_RANGE );


  TEST( parseStartTime( clockDecimal, "-12:34:56" ) == ERR_HR_RANGE );
  TEST( parseStartTime( clockDecimal, "12:-34:56" ) == ERR_MIN_RANGE );
  TEST( parseStartTime( clockDecimal, "12:34:-56" ) == ERR_SEC_RANGE );

  TEST( parseStartTime(clockDecimal, "-12:-34:-56" ) ==
    (ERR_HR_RANGE | ERR_MIN_RANGE | ERR_SEC_RANGE) );

  TEST( parseStartTime(clockDecimal, "25:66:66" ) ==
    (ERR_HR_RANGE | ERR_MIN_RANGE | ERR_SEC_RANGE) );

  TEST( parseStartTime(clockDecimal, "12:a:66" ) ==
    (ERR_MIN_VALUE | ERR_SEC_RANGE) );

  TEST( parseStartTime(clockDecimal, "aaa:334b:12345" ) ==
    (ERR_HR_VALUE | ERR_MIN_VALUE | ERR_SEC_RANGE) );
  
}

int main( void ) {

  fprintf(stderr, "Running tests for parseStartTime...\n");
  testparseStartTime();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}

