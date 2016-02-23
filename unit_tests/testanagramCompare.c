/*
 * Filename: testanagramCompare.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: Tester for anagramCompare()
 */

#include <stdio.h>

#include "pa3.h"
#include "test.h"


/*
 * TODO Function headers are always needed!
 */
static void testanagramCompare() {
  
    struct anagram a;
    struct anagram b;
    struct anagram c;
    struct anagram d;
    struct anagram e;
    struct anagram f;
    
    createAnagram("happy", &a);
    createAnagram("hello", &b);
    TEST(anagramCompare(&a, &b) == -1);

    createAnagram("Today", &c);
    createAnagram("today", &d);
    TEST(anagramCompare(&c, &d) == -1);

    createAnagram("today", &c);
    createAnagram("Today", &d);
    TEST(anagramCompare(&c, &d) == 1);

    createAnagram("today", &c);
    createAnagram("today", &d);
    TEST(anagramCompare(&c, &d) == 0);
 
    createAnagram("Zebra", &e);
    createAnagram("Apple", &d);
    TEST(anagramCompare(&e, &f) == 1);
}

/*
 * TODO Function headers are always needed!
 */
int main( void ) {
  (void) fprintf( stderr, "Starting testanagramCompare\n" );

  testanagramCompare();

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}

