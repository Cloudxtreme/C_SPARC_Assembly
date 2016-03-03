/*
 * filename: teststrIgnoreCaseCmp.c
 * author: TODO: enter your name
 * userid: TODO: enter your cs30x login id
 * description: tester for strIgnoreCaseCmp
 */

#include  <stdio.h>
#include  <strings.h>

#include  "pa4.h"
#include  "test.h"

static void teststrIgnoreCaseCmp() {
  char * lhs = "ABC";
  char * rhs = "abc";
  int n = strlen(lhs);
  TEST( strIgnoreCaseCmp( lhs, rhs, n ) == 0 );

  rhs = "aba";
  TEST( strIgnoreCaseCmp( lhs, rhs, n ) == 1 );
  TEST( strIgnoreCaseCmp( rhs, lhs, n ) == -1 );

  /* TODO Come up with more test cases */
  
  lhs = "abc";
  rhs = "ab";
  TEST( strIgnoreCaseCmp( lhs, rhs, n ) == 1 );
  TEST( strIgnoreCaseCmp( rhs, lhs, n ) == -1 );
  
  lhs = "Hellz";
  rhs = "hella";
  TEST( strIgnoreCaseCmp( lhs, rhs, 5 ) == 1 );
  TEST( strIgnoreCaseCmp( rhs, lhs, 5 ) == -1 );

  lhs = "lexicographical order";
  rhs = "lexicographical order";
  n = strlen(lhs);
  TEST( strIgnoreCaseCmp( lhs, rhs, n ) == 0 );
  

}

int main() 
{
  (void) fprintf( stderr, "Starting teststrIgnoreCaseCmp\n" );

  teststrIgnoreCaseCmp();

  (void) fprintf( stderr, "Done.\n" );

  return 0;

}
