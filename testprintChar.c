/*
 * Filename: testprintChar.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Unit test program to test the function printChar.
 * Date: 1/19/2106
 * Sources of Help: PA1 Assignment Specification
 */ 

#include <stdlib.h> /* For rand() function prototype */
#include "pa1.h"  /* For isOdd() function prototype */

/*
 * void printChar( char ch );
 *
 * Prints char ch to stdout
 */

void
testprintChar() {
    printf( "Testing printChar()\n" );
    printChar( 'A' );
    printChar( 'B' );
    printChar( 'C' );
    printChar( '\n' );

    printf( "Finished running tests on printChar()\n" );
}

int
main() {
    testprintChar();

    return 0;
}

