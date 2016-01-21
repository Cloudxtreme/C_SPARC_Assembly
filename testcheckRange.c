/*
 * Filename: testcheckRange.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Unit test program to test the function checkRange.
 * Date: 1/19/2106
 * Sources of Help: PA1 Assignment Specification
 */ 

#include <stdlib.h> /* For rand() function prototype */
#include <limits.h> /* For LONG_MIN and LONG_MAX */
#include "pa1.h"  /* For checkRange() function prototype */
#include "test.h" /* For TEST() macro and stdio.h */

/*
 * long checkRange(long minRange, long offset, long value);
 *
 * Returns 1 if value is within minRange plus offset, inclusive.
 * Returns -1 if offset is negative.
 * Returns 0 otherwise (value is not with minRange plus offset).
 */

void
testcheckRange() {
    printf( "Testing checkRange()\n" );
    // Edge cases
    TEST( checkRange( -1, 0, -1 ) == 1 );
    TEST( checkRange( -1, 5, 4 ) == 1 );
    
    // Random inputs
    TEST( checkRange( 5, 5, 6 ) == 1 );
    TEST( checkRange( 6, 6, 7 ) == 1 );

    // Out of range cases    
    TEST( checkRange( 6, 4, 5 ) == 0 );
    TEST( checkRange( -1, 6, 6 ) == 0 );
    
    // Negative offset
    TEST( checkRange( -1, -1, 6 ) == -1 );

    // TODO: Add more test cases (consider all cases)

    printf( "Finished running tests on checkRange()\n" );
}

int
main() {
    testcheckRange();

    return 0;
}

