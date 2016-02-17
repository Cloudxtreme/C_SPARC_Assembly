/*
 * Filename: testcharCompare.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: Tester for charCompare
 */

#include <stdio.h>

#include "pa3.h"
#include "test.h"

/*
 * TODO Function headers are always needed!
 */
static void testcharCompare() {
  char lhs = 'a';
  char rhs = 'a';
  TEST( charCompare( &lhs, &rhs ) == 0 );

  lhs = 'a';
  rhs = 'b';
  TEST( charCompare( &lhs, &rhs ) == -1 );
  TEST( charCompare( &rhs, &lhs ) == 1 );

  /* TODO Come up with more test cases */
}

/*
 * TODO Function headers are always needed!
 */
int main( void ) {
  (void) fprintf( stderr, "Starting testcharCompare\n" );

  testcharCompare( );

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}
