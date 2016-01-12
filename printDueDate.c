/*
 * Filename: printDueDate.c 
 * Author: : Moiz Qureshi
 * Userid: cs30xix
 * Description: Example C routine to print out the due date info
 *              (month, day, year) using a pointer to a structure
 *              Called from main()
 * Date: Jan. 10, 2016
 * Sources of Help: PA0 Assignment Sheet, PA0 Code Handout
 */

#include <stdio.h>
#include "pa0_strings.h"

/*
 * Function name: printDueDate()
 * Function prototype:
 *    void printDueDate( const struct DueDate *dueDate );
 * Description: Prints to stdout the month, day, and year members of a 
 *              struct DueDate node.
 * Parameters: 
 *      arg1: struct DueDate *dueDate -- pointer to the 
 *            DueDate struct which should be printed
 * Side Effects: Outputs the due date of the assignment
 * Error Conditions: Checks to make sure arg1 is not NULL
 *                   No checks to ensure struct data are correct type/values.
 * Return Values: None.
 */

void
printDueDate( const struct DueDate *dueDate ) {
  if ( dueDate != NULL)
    (void) printf( STR_DUEDATE, dueDate->month, dueDate->day, dueDate->year );
}

