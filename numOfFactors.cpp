/* Filename: numOfFactors.cpp
 * Author: Moiz Qurehsi 
 * Userid: cs30xix
 * Description: Calculates the number of factors of the number n passed in,
 *              within the given range from lo to hi.
 * Date: 2/27/16
 */

/*
 * Function name: numOfFactors()
 *
 * Function prototype: long long numOfFactors( long long n,
 *                                             long long lo,
 *                                             long long hi );
 *
 * Params: n is the value we are checking to determine how many factors
 *         evenly divide into it.
 *         lo is the low (inclusive) range of possible factors to check.
 *         hi is the high (exclusive) range of possible factors to check.
 *
 * Algorithm:
 *   if n <= 1 return 0 (we won't deal with values less than 2). By definition,
 *       prime numbers are greater than 1.
 *
 *   if lo <= 1, set lo to 2 (we won't deal with factors less than 2).
 *
 *   loop thru the range [lo, hi) as factors incrementing by 1 each time
 *       thru the loop checking if n is evenly divisible by each factor.
 *       If it is evenly divisible, increment the number of
 *       evenly-divisible factors for this range.
 *   
 *   There may be other more efficient algorithms, but this will do.
 *   We want to see how multi-threading in C++11 with async()/get()
 *   might improve overall performance.
 *
 * Side Effects: None.
 *
 * Error Conditions: None.
 *
 * Return value: long long int indicating the number of evenly-divisible
 *               factors in n.
 */

long long numOfFactors( long long n, long long lo, long long hi ) {
  /* Local Variables */
  long long factorCount = 0;    // holds value for # of factors for long long n
  
  // If n is <= 1, then return 0; not dealing with values less than 2
  if (n <= 1) {
    return 0;
  }
  
  // If lo is <= 1, then set lo = 2; wont deal with factors less than 2
  if (lo <= 1) {
    lo = 2;
  }

  /* Loop thru range of lo to hi, see if num is divisible by loop counter.
   * If it is then increase factorCount by 1, if not, then increase loop 
   * counter and repeat.
   */
  for (long long i = lo; i < hi; i++) {
    if( (n % i)  == 0 ) {
      factorCount +=1;
    }
  }
  
  // Return the value of # of factors of long long n
  return factorCount;
}

