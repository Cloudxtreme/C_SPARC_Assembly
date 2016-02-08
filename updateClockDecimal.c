/*
 * Filename: uodateClockDecimal.c 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Calls updateClockDecimalValue() with correct parameters passed
 *              in, in order to update the values for horus, minutes, and
 *              seconds
 * Date: 2/8/16
 * Sources of Help: PA2 Assignment Sheet, PA2 Discussion Slides pt.2
 */

/*
 * Header files included here.
 * Standard C library header first, then local headers.
 */
#include <stdio.h>
#include "pa2.h"
#include "pa2Strings.h"

/*
 * Function name: updateClockDecimal() 
 *
 * Function prototype: 
 *  void updateClockDecimal( long clockDecimal[], long intervalSeconds );
 *
 * Description: Calls updateClockDecimalValue() three times, for each of the 
 *              three segments: hours, minutes, and seconds. Uses the carry
 *              out to pass into next succesive updateClockDecimalValue()
 *              function call as updateAmt.
 *          
 * Parameters: 
 *      arg 1 - long clockDecimal[] - array containing hours, mins, and secs
 *      arg 2 - long intervalSeconds - amount of time in seconds to increment
 *                                     the clock by
 *
 * Side Effects: Updates the hours, minutes, and seconds of the BCD clock's 
 *               decimal time in clockDecimal array
 *              
 * Error Conditions: None
 *      
 * Return Value: None
 */


