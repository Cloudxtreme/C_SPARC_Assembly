/*
 * Filename: printChar.s
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Prints char passed in as argument to stdout. Just prints a 
 * 		single character
 * 		Called from line()
 * Date: 1/24/2016
 * Sources of help: PA1 Assignment Sheet, PA1 Discussion Slides Pt.2,
 * 		    PA0 Code Handout (printWelcome.s)
 */

	.global printChar	! Declares the symbol to be globally visible
				! so we can can call this function from
				! other modules
	
	.section ".data"	! The data segment begins here
fmt:				! Formatted string used for printf()
	.asciz "%c"		


	.section ".text"	! The text segment begins here

/*
 * Function name: printChar()
 * Function prototype: void printChar( char ch );
 * Description: Prints one char at a time, char is argument that is passed in
 * Parameters:
 * 	arg 1: char ch -- char to be printed once
 * Side Effects: Just prints char ch once
 * Error Conditions: None (input error checking done in pa1.c)
 * Return Values: None
 *
 * Registers Used:
 * 	%i0 - arg 1 -- char ch
 */

printChar:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was 
				! calculated
	
	set	fmt, %o0	! Format Striing
	mov 	%i0, %o1	! Copy of parameter (char ch) to print
	call 	printf		! Make printf function call
	nop			! Delay slot for call instruction

	ret			! Return from subroutine
	restore			! Restore caller's window; in "ret" delay slot



