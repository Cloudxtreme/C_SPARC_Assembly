/*
 * Filename: pa4.s 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Driver for myuniq program where main() function is.
 * Date: 3/6/2017 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.2
 */

	.global main		! Declare the symbol to be globally visible,
				! more importantly, compiler will be able to 
				! see main() function for this program

	.section ".textt"	! The text segment begins here

LOCAL_VAR_BYTES = 1044
ERROR_INFO_OFFSET = 1028
ARG_INFO_OFFSET = 1044

/*
 * Function name: main()
 *
 * Function prototype: int main( int argc, char *argv[] );
 *
 * Description: Driver for the myuniq program where we call parseArgs(), check
 * 		argument errors, check the if the help flag was set and print
 * 		the long usage message, then call runUniq() if there were no
 * 		errors, if there were errors after, then call printErrors() 
 * 		and return with sucess or failure, if there weren't errors, or
 *		if there were errors, respectively. 
 *          
 * Parameters: 
 *      arg 1 - int argc -- number of command line arguents passed in including
 *      		    the program name
 *      arg 2 - char *argv[] -- pointer to strings of arguments passsed in
 *
 * Side Effects: Runs the myuniq program and checks for any errors.
 * 
 * Error Conditions: None in main(), however errors can occur in functions that
 * 		     main() calls. All errors are stored in the errorInfo 
 * 		     struct and printed by printErrors()
 *
 * Return Values: 
 * 	exitSuccess - if there were no errors in running of program
 * 	exitFailure - if an error occurred during the running of the program
 * 		
 * Registers Used: 
 * 	
 * 	%i0 - int argc
 * 	%i1 - char *argv[]
 * 
 * 	%l0 - base address of struct errorInfo (%fp-1028)
 * 	%l1 - base adress  of struct argInfo (%fp-1044)
 *	%l2 - struct errorInfo errorCode member value
 * 	%l3 - int ErrorCodeErrNone (ErrNone check)
 *	%l4 - struct argInfo options member value
 *	%l5 - int FlagHelp (OPT_HELP check)
 *
 */

main:
	/* Save the caller's window. Use the formula from lecture notes
	 * to determine how much space to allocate on the stack. We are adding
	 * 1140 becuase that is the number of bytes of local variables in 
	 * main(). Specifically 1028 bytes for struct errorInfo and 16 bytes
	 * for struct argInfo, which we are allocating on the stack.
	 */
	save	%sp, -(92 + LOCAL_VAR_BYTES) & -8, %sp	 
	
	mov	%i0, %o0
	mov	&i1, %o1

	sub	%fp, ERROR_INFO_OFFSET, %l0
	sub	%fp, ARG_INFO_OFFSET, %l1

	mov	%l0, %o2
	mov 	%l1, %o3

	call 	parseArgs
	nop

	ld	[%l0], %l2
	set	ErrCodeErrNone, %l3
	ld	[%l3], %l3

	cmp	%l2, %l3
	bne	parseArgErr
	nop

	set 	ArgInfoOptionsOffset, %l4
	ld	[%l4], %l4
	add	%l0, %l4, %l4
	ld	[%l4], %l4

	set	FlagHelp, %l5
	ld	[%l5], %l5

	cmp	%l4, %l5


parseArgErr:
	mov 	%l0, %o0
	mov	%i1, %o1

	call 	printErrors
	nop

	set	ErrorFailure, %i0
	ld	[%i0], %i0
	ret
	restore
