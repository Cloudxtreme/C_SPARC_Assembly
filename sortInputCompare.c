/*
 * Filename: sortInputCompare.c  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Compares two lines of user inputted strings
 * Date: 3/1/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.1
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>
#include <string.h>

#include "pa4.h"

/*
 * Function name: sortInputCompare() 
 *
 * Function prototype: int sortInputCompare( const void *p1, const void *p2 );
 *
 * Description: Compares two lines of user inputted string by calling the 
 *              strcmp() function.
 *          
 * Parameters: 
 *      arg 1 - const void *p1 -- user inputted string #1
 *      arg 2 - const void *p2 -- user inputted string #2
 *
 * Side Effects: Compares two strings to see if one is less than the other
 *               or if they are equal.
 *              
 * Error Conditions: None 
 *      
 * Return Value: 
 *    1 - if the first string is greater
 *    0 - if the strings are equal
 *   -1 - if the second string is greater
 *
 */

int
sortInputCompare( const void *p1, const void *p2 ) {
  /* Local Variables */
  int result = 0;   // holds result from strcmp() functionc call

  // Call strcmp function and store return value in result var
  result = strcmp(p1, p2);
  
  // If string 1 was greater than string 2, then result = 1
  if (result > 0) {
    result = 1;
  }
  // If string 1 and string 2 are equal, then result = 0
  else if (result == 0) {
    result = 0;
  }
  // If string 2 was greater than string 1, then result = -1
  else if (result < 0) {
    result = -1;
  }
  // return result value from this function
  return result;
}

