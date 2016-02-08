/*
 * Filename: testusage.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Unit test program to test the function usage().
 * Date: 2/7/2106
 * Sources of Help: None
 */ 

// First Library Header, then local ones
#include <stdio.h>
#include "pa2.h"

// Function prototype
void testusage();

void testusage() {
  usage( "BCDIntervalClock" );

}

int main( void ) {

  // Performing Visual test since we need to see if usage() is printing
  // usage message correctly. 
  fprintf(stderr, "Running tests for usage()...\n");
  testusage();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}

