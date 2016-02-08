/*
 * Filename: testdisplayBCDClock.c
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Unit test program to test the function displayBCDClock().
 * Date: 2/7/2106
 * Sources of Help: None
 */ 

// First Library Header, then local ones
#include <stdio.h>
#include "pa2.h"

// Function prototype
void testdisplayBCDClock();

void testdisplayBCDClock() {

  unsigned char clockBCD[3];
  
  clockBCD[0] = 0x15;
  clockBCD[1] = 0x03;
  clockBCD[2] = 0x27;

  displayBCDClock( clockBCD );

}

int main( void ) {

  // Performing Visual test since we need to see if displayClockBCD is printing
  // correctly. 
  fprintf(stderr, "Running tests for displayBCDClock()...\n");
  testdisplayBCDClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
