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
	
	.section ".text"	! The text segment begins here

LOCAL_VAR_BYTES = 1044
ERROR_INFO_OFFSET = -1028
ARG_INFO_OFFSET = -1044

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
 *	%l6 - int UsageModeUsageLong (UsageLong)
 *	%l7 - FILE *StandardOut (stdout)
 */

main:
	/* Save the caller's window. Use the formula from lecture notes
	 * to determine how much space to allocate on the stack. We are adding
	 * 1140 becuase that is the number of bytes of local variables in 
	 * main(). Specifically 1028 bytes for struct errorInfo and 16 bytes
	 * for struct argInfo, which we are allocating on the stack.
	 */
	save	%sp, -(92 + LOCAL_VAR_BYTES) & -8, %sp	 

	/* Clear the local registers used */
	clr	%l0
	clr	%l1
	clr	%l2
	clr	%l3
	clr	%l4
	clr	%l5
	clr 	%l6
	clr	%l7
	
	mov	%i0, %o0 	! Copy argc to %o0
	mov	%i1, %o1	! Copy argv to %o1

	/* Get the address of struct errorInfo and store in %l0 */
	add	%fp, ERROR_INFO_OFFSET, %l0

	/* Get the address of struct argInfo and store in %l1 */
	add	%fp, ARG_INFO_OFFSET, %l1

	mov	%l0, %o3	! Copy struct errorInfo pointer to %o3
	mov 	%l1, %o2	! Copy struct argInfo pointer to %o2

	call 	parseArgs	! Call parseArgs, passing in args stored that
	nop			! were stored in out registers
	
	/* Get the struct errorInfo errorCode offset, load into %l2 */
	set	ErrorInfoErrorCodeOffset, %l2
	ld	[%l2], %l2
	
	/* Add errorCode offset to struct errorInfo pointer, then load value
	 * of errorCode into %l2
	 */
	add	%l0, %l2, %l2
	ld	[%l2], %l2
	
	/* Get the value of ErrNone, and store into %l3 */
	set	ErrorCodeErrNone, %l3
	ld	[%l3], %l3
	
	/* Compare the errorCode member of struct errorInfo with ErrNone.
	 * If they are not equal, then branch to ErrorExit, otehrwise
	 * continue.
	 */
	cmp	%l2, %l3	
	bne	ErrorExit
	nop
	
	/* Get the struct argInfo option offset, then load value of options 
	 * offset into %l4.
	 */
	set 	ArgInfoOptionsOffset, %l4
	ld	[%l4], %l4

	/* Add the options offset to struct argInfo pointer, then load value 
	 * of options back into %l4
	 */
	add	%l1, %l4, %l4
	ld	[%l4], %l4

	/* Get the value of FlagHelp (OPT_HELP), and store into %l5 */
	set	FlagHelp, %l5
	ld	[%l5], %l5

	/* Compare the options member of struct argInfo with OPT_FLAG. If they
	 * are not equal then branch to RunUniq. Otherwise continue, and call
	 * usage(), passing correct parameters. 
	 */
	cmp	%l4, %l5
	bne	RunUniq
	nop

	/* Get the value of StandardOut (stdout), and store it into %o0	*/
	set	StandardOut, %l7
	ld	[%l7], %o0

	/* Get the value of UsageModeUsageLong (UsageLong), and store it into
	 * %o1
	 */
	set	UsageModeUsageLong, %l6
	ld	[%l6], %o1

	/* Get the progName string from argv[0], and store into %o2 */
	ld	[%i1], %i1
	mov	%i1, %o2	

	/* Call usage() */
	call 	usage
	nop

	/* Branch to SuccessExit */
	ba	SuccessExit
	nop

ErrorExit:
	/* Copy pointer to struct errorInfo to %o0 */
	mov 	%l0, %o0

	/* Get the progName string from argv[0], and store into %o1 */
	ld	[%i1], %i1
	mov	%i1, %o1
	
	/* Call printErrors() */
	call 	printErrors
	nop

	/* Since there were errors, get value of exitFailure (EXIT_FAILURE), 
	 * and store into %i0, which we will return from this function
	 */
	set	exitFailure, %i0
	ld	[%i0], %i0
	
	ret			! Return from subroutine
	restore			! Return caller's window; in ret's delay slot

RunUniq:
	/* Copy struct errorInfo pointer to %o1 */
	mov	%l0, %o1

	/* Copy struct argInfo pointer to %o0 */
	mov	%l1, %o0

	/* Call runUniq() */
	call 	runUniq
	nop	
	
	/* Check to see errorCode member of struct errorInfo is equal to
	 * errNone, if it isnt branch to ErrorExit, otherwise continue below
	 * to SuccessExit
	 */
	ld	[%l0], %l2
	cmp 	%l2, %l3
	bne	ErrorExit
	nop

SuccessExit:
	/* Get value of exitSuccess (EXIT_SUCCESS), and store value into
	 * %i0, so we can return that value from this function.
	 */
	set	exitSuccess, %i0
	ld	[%i0], %i0
	
	ret			! Return from subroutine	
	restore			! Return caller's window; in ret's delay slot


