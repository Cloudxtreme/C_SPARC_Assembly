/*
 * Filename: testline.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Unit test program to test the function line().
 * Date: 1/19/2106
 * Sources of Help: PA1 Assignment Specification
 */ 

#include <stdlib.h> /* For rand() function prototype */
#include "pa1.h"  /* For isOdd() function prototype */

/*
 * void line ( char xorChar, long charpos, long width );
 *
 * Prints line of xorChar at charpos or all spaces
 */

void
testline() {
    printf( "Testing line( )\n" );
    
    line( 'A', 5, 10 );
    printf( "\n" );

    line( 'A', 5, 4 );
    printf( "\n" );



    printf( "Finished running tests on line()\n" );
}

int
main() {
    testline();

    return 0;
}

