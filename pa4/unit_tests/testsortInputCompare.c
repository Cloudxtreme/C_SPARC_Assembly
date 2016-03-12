/*
 * filename: testsortInputCompare.c
 * author: Moiz Qureshi 
 * userid: cs30xix
 * description: tester for sortInputCompare
 */

#include  <stdio.h>

#include  "pa4.h"
#include  "test.h"

static void testsortInputCompare() {
  char * lhs = "abc";
  char * rhs = "abc";
  TEST( sortInputCompare( &lhs, &rhs ) == 0 );

  rhs = "abd";
  TEST( sortInputCompare( &lhs, &rhs ) < 0 );
  TEST( sortInputCompare( &rhs, &lhs ) > 0 );

  lhs = "ZZZ";
  TEST( sortInputCompare( &lhs, &rhs ) < 0 );

}

int main() {
  (void) fprintf( stderr, "Starting testsortInputCompare\n" );

  testsortInputCompare();

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}
