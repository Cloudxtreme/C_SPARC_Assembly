/*
 * Filename: printWelcome.s 
 * Author: : Moiz Qureshi
 * Userid: cs30xix
 * Description: Example SPARC assebly routine to print out a greeting followed
 * 		by string (sudent's name) passed in as an argument
 * 		to this function.
 * 		Called from main()
 * Date: Jan. 10, 2016
 * Sources of Help: PA0 Assignment Sheet, PA0 Code Handout
 */

	.global printWelcome	! Declares the symbol to the globally visible so
				! we can call this function from other modules

	.section ".data"	! The data segment begins here
fmt:				! Formatted string used for printf()
	.asciz	"Welcome to CSE 30, %s\n"


	.section ".text"     ,  ! The text segment begins here

/*
 * Function name: printWelcome()
 * Function prototype: void printWelcome( const char *str );
 * Description: Prints to stdout a greeting string and the argument
 * 		with a terminating newline via printf()
 * Parameters:
 * 	arg 1: char *str -- the string to print after the greeting
 *
 * Side Effects: Outputs greeting with string supplied as argument.
 * Error Conditions: None. [Arg 1 is not checked to ensure it is not NULL.]
 * Return Value: None
 *
 * Register Used:
 * 	%i0 - arg 1 -- the string (char *) passed in to this function
 *
 * 	%o0 - param 1 to printf() -- format string
 * 	%o1 - param 2 to printf() -- copy of arg 1 being passed in
 */

printWelcome:
	save 	%sp, -96, %sp	! Save caller's window; if different than -96
				! then comment on how that value is calculated

	set	fmt, %o0	! Format string
	mov	%i0, %o1	! Copy of formal parameter to print
	call	printf		! Make function call
	nop			! Delay slot for call instruction

	ret			! Return from subroutine
	restore			! Restore caller's window; in "ret" delay slot

