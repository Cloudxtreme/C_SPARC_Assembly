/*
 * Filename: testhashKeyMemberCompare.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: Tester for hashKeyMemberCompare()
 */

#include <stdio.h>

#include "pa3.h"
#include "test.h"


/*
 * TODO Function headers are always needed!
 */
static void testhashKeyMemberCompare() {
  
    struct anagram a;
    struct anagram b;
    struct anagram c;
    struct anagram d;
    struct anagram e;
    struct anagram f;
    
    createAnagram("happy", &a);
    createAnagram("hello", &b);
    TEST(hashKeyMemberCompare(&a, &b) == -1);

    createAnagram("today", &c);
    createAnagram("Today", &d);
    TEST(hashKeyMemberCompare(&c, &d) == 0);

    createAnagram("Zebra", &e);
    createAnagram("Apple", &d);
    TEST(hashKeyMemberCompare(&e, &f) == 1);
}

/*
 * TODO Function headers are always needed!
 */
int main( void ) {
  (void) fprintf( stderr, "Starting testhashKeyMemberCompare\n" );

  testhashKeyMemberCompare();

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}

