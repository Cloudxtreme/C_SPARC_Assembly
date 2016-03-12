/*
 * filename: teststrIgnoreCaseCmp.c
 * author: Moiz Qureshi 
 * userid: cs30xix
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
  
  lhs = "zebra";
  rhs = "a";
  n = strlen(lhs);
  TEST( strIgnoreCaseCmp( lhs, rhs, n ) == 1 );
  
  lhs = "ze\0bra";
  rhs = "zebra";
  n = strlen(rhs);
  TEST( strIgnoreCaseCmp( lhs, rhs, n ) == -1 );
  
  lhs = "abcd";
  rhs = "abc";
  n = strlen(lhs);
  TEST( strIgnoreCaseCmp( lhs, rhs, n ) == 1 );
  
  lhs = "";
  rhs = "";
  n = strlen(lhs);
  TEST( strIgnoreCaseCmp( lhs, rhs, 0 ) == 0 );

}

int main() 
{
  (void) fprintf( stderr, "Starting teststrIgnoreCaseCmp\n" );

  teststrIgnoreCaseCmp();

  (void) fprintf( stderr, "Done.\n" );

  return 0;

}
