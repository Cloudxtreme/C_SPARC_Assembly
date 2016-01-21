/*
 * Filename: testisOdd.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Unit test program to test the function isOdd.
 * Date: 1/19/2106
 * Sources of Help: PA1 Assignment Specification
 */ 

#include <stdlib.h> /* For rand() function prototype */
#include "pa1.h"  /* For isOdd() function prototype */
#include "test.h" /* For TEST() macro and stdio.h */

/*
 * long isOdd( long num);
 *
 * Returns 1 if num is odd.
 * Returns 0 otherwise, num is not odd.
 */

void
testisOdd() {
    printf( "Testing isOdd()\n" );
    
    // Test Odd Numbers
    TEST( isOdd( 1 ) == 1 );
    TEST( isOdd( 3 ) == 1 );
    TEST( isOdd( -3 ) == 1 );

    //  Test Even Numbers
    TEST( isOdd( 4 ) == 0 );
    TEST( isOdd( 16 ) == 0 );
    TEST( isOdd( -16 ) == 0 );

    // Test 0
    TEST( isOdd( 0 ) == 0 );

    printf( "Finished running tests on isOdd()\n" );
}

int
main() {
    testisOdd();

    return 0;
}
