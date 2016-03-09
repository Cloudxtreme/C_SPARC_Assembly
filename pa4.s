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

	clr	%l0
	clr	%l1
	clr	%l2
	clr	%l3
	clr	%l4
	clr	%l5
	clr 	%l6
	clr	%l7
			
	mov	%i0, %o0
	mov	%i1, %o1

	add	%fp, ERROR_INFO_OFFSET, %l0
	add	%fp, ARG_INFO_OFFSET, %l1

	mov	%l0, %o3
	mov 	%l1, %o2

	call 	parseArgs
	nop
	
	set	ErrorInfoErrorCodeOffset, %l2
	ld	[%l2], %l2

	add	%l0, %l2, %l2
	ld	[%l2], %l2

	set	ErrorCodeErrNone, %l3
	ld	[%l3], %l3

	cmp	%l2, %l3
	bne	ErrorExit
	nop

	set 	ArgInfoOptionsOffset, %l4
	ld	[%l4], %l4
	add	%l1, %l4, %l4
	ld	[%l4], %l4

	set	FlagHelp, %l5
	ld	[%l5], %l5

	cmp	%l4, %l5
	bne	RunUniq
	nop

	set	StandardOut, %l7
	ld	[%l7], %o0

	set	UsageModeUsageLong, %l6
	ld	[%l6], %o1

	ld	[%i1], %i1
	mov	%i1, %o2	

	call 	usage
	nop

	ba	SuccessExit
	nop

ErrorExit:
	mov 	%l0, %o0
	ld	[%i1], %i1
	mov	%i1, %o1

	call 	printErrors
	nop

	set	exitFailure, %i0
	ld	[%i0], %i0
	ret
	restore

RunUniq:
	mov	%l0, %o1
	mov	%l1, %o0

	call 	runUniq
	nop	

	ld	[%l0], %l2
	cmp 	%l2, %l3
	bne	ErrorExit
	nop

SuccessExit:
	set	exitSuccess, %i0
	ld	[%i0], %i0
	ret	
	restore


