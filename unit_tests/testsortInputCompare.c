/*
 * filename: testsortInputCompare.c
 * author: TODO: enter your name
 * userid: TODO: enter your cs30x login id
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

  /* TODO Come up with more test cases */
}

int main() {
  (void) fprintf( stderr, "Starting testsortInputCompare\n" );

  testsortInputCompare();

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}
