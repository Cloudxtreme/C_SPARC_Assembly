/*
 * Filename: sequentialSquaredSumMinMax.cpp
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Iterates through array of elements from lo to hi and calculates
 *              the squared sum (sum of aquares of each element), determines
 *              the min and max values in the sequence.
 * Date: 2/19/16
 */

#include "pamt1.h"

/*
 * Function name: sequentialSquaredSumMinMax()
 *
 * Function prototype: 
 *    struct result sequentialSquaredSumMinMax( char a[], int lo, int high );
 *
 * Description: Iterates through array of elements from lo to hi and calculates
 *              the squared sum (sum of aquares of each element), determines
 *              the min and max values in the sequence. All the results of 
 *              these operations are stored in struct result and that struct
 *              is returned from this function.
 *              
 * Parameters: 
 *    arg 1 - char a[] -- array containing random numbers
 *    arg 2 - int lo -- inclusive lowerbound index of char a[]
 *    arg 3 - int hi -- inclusive upperbound index of char a[]
 *
 * Side Effects: Calculates the squared sum of values in array, finds the
 *               min and max; and stores these results into struct result,
 *               which the function will return
 *
 * Error Conditions: None.
 *
 * Return Value: struct result -- contains results of operations of finding 
 *                                squared sum, min, and max.
 *
 *
 */

struct result
sequentialSquaredSumMinMax( char a[], int lo, int hi ) {
  
  /* Local Variables */
  struct result result;       // Struct to store calculates results
  
  long value;                 // long to hold value of number @ array index
  int i;                      // integer as for-loop counter
  

  // Set inital values of struct result members
  result.max = a[lo];
  result.min = a[lo];
  result.sum = 0;

  // Check if lo and hi array indices are positive (cannot have negative index)
  if ( lo < 0 || hi < 0 ) {
    return result;    
  }


  for (i = lo; i < hi; i++) {
    
    // Get value at index of array
    value = a[i];   

    // Calculates squared sums and save in result struct;
    result.sum += value*value;   

    /* Find min and max.
     * If value is less than result.min then set new min
     * If value is greater than result.max then set new max
     */
    if ( value < result.min ) {
      result.min = value;
    }

    if ( value > result.max ) {
      result.max = value;   
    }
  }

  return result;

}
