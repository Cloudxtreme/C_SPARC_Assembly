/*
 * Filename: main.c 
 * Author: : Moiz Qureshi
 * Userid: cs30xix
 * Description: Example C program for pa0. It calls a couple of functions
 *              written in assembly and C as examples of function calls and 
 *              parameter passin in C ans SPARC assembly (also known as
 *              the language's and architechture's calling conventions)
 * Date: Jan. 10, 2016
 * Sources of Help: PA0 Assignment Sheet, PA0 Code Handout
 */

/*
 * Header files included here.
 * Std C Lib header files first, then local headers.
 */
 
/* Standard C Library Headers use angle brackets < > */
#include <stdlib.h>
#include <stdio.h>  // Since we are using fprintf()

/* Local headers use double quotes " " */
#include "pa0.h"
#include "pa0_strings.h"

/*
 * Function name: main()
 * Function prototype: int main( int argc, char *argv[] );
 *                              or
 *                     int main( void ); if no command line processing.
 * Description: C main driver which call C and SPARC assmebly routines to
 *              print a greeting, assignment due date, and the square of the
 *              number entered at the command line.
 * Parameters: int containing the number to square
 * Side Effects: Outputs greeting, assignment due date, and square of a number
 * Error Conditions: None.
 * Return Value: EXIT_FAILURE indicating failed execution, and EXIT_SUCCESS_
 *               indicating successful execution.
 */

int
main( int argc, char *argv[] ) {
  struct DueDate dueDate;    /* Structure to hold assignment due date */
  int argVal = 0;            /* Value to square from command line */

  /*
   * We decrement argc because the name of the program is the first
   * argument which we do not want to count.
   */
  --argVal;

  if( argc != EXPECTED_ARGS ) {

    /* Error messages are printed to stderr */
    (void) fprintf(
        stderr,
        argc < EXPECTED_ARGS ? STR_ERR_MISSING_ARG : STR_ERR_EXTRA_ARG,
        argv[0] );

    (void) fprintf( stderr, STR_ERROR_USAGE, argv[0] );

    return EXIT_FAILURE;
  }

  /*
   * strtol() offers error checking/handling. See: man strtol
   */
  argVal = atol( argv[1] );

  /*
   * TODO: Update the assignment due date. Make sure only the first letter in 
   * the month name is capitalized. E.g. Decemeber, January, etc.
   */
  dueDate.day   = 12;
  dueDate.year  = 2016;
  dueDate.month = "January";

  /*
   * Print the greeting message
   */
  printWelcome( STR_WELCOME_QUARTER );

  /*
   * Print assignment due date
   * printDueDate() takes the address of the DueDate struct
   * (a pointer to the DueDate struct)
   */
  printDueDate( dueDate );

  /*
   * Now square the input and print the result
   */
  (void) printf( STR_SQUARENUM, argv[1], squareNum( argVal ) );
}


