/*
 * Filename: testisNegative.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Unit test program to test the function isNegative.
 * Date: 1/19/2106
 * Sources of Help: PA1 Assignment Specification, Lecture #4 Notes
 *                  PA! Discussion Slides
 */ 

#include <stdlib.h> /* For rand() function prototype */
#include "pa1.h"  /* For isNegative() function prototype */
#include "test.h" /* For TEST() macro and stdio.h */

/*
 * long isNegative( long num);
 *
 * Returns 1 if num is negative.
 * Returns 0 otherwise, num is not negative.
 */

void
testisNegative() {
    printf( "Testing isNegative()\n" );
    
    // Test Negative Numbers
    TEST( isNegative( -1 ) == 1 );
    TEST( isNegative( -20 ) == 1 );

    //  Test Positive Numbers
    TEST( isNegative( 4 ) == 0 );
    TEST( isNegative( 16 ) == 0 );

    // Test 0
    TEST( isNegative( 0 )  == 0 );

    printf( "Finished running tests on isNegative()\n" );
}

int
main() {
    testisNegative();

    return 0;
}


