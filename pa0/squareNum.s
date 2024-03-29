/*
 * Filename: squareNum.s 
 * Author: : Moiz Qureshi
 * Userid: cs30xix
 * Description: Example SPARC assebly routine to square a single argument and
 * 		return the result.
 * 		Called from main()
 * Date: Jan. 10, 2016
 * Sources of Help: PA0 Assignment Sheet, PA0 Code Handout
 */

	.global squareNum	! Decalres the symbol to be globally visible so
				! we can call this function from other modules.

	.section ".text"	! The text segment begins here

/*
 * Function name: squareNum()
 * Function prototype: int squareNum( int num );
 * Description: Squares num and returns the result
 * Parameters:
 * 	arg 1: int num -- number to be squared
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: Square of num
 *
 * Registers Used:
 * 	%i0 - arg 1 -- 1st number to be squared; also used to return the result
 */

squareNum:
	save	%sp, -96, %sp	! Save caller's window; if different than -96
				! then comment on how that value was calculated

	mov	%i0, %o0	! Put a copy of the parameter in the registers
				! %o0 and %o0 to be used by .mul.
	mov	%i0, %o1

	call 	.mul		! This is a transfer of control instruction and
	nop			! must be followed by a nop instruction
	

	mov 	%o0, %i0	! .mul's return value is in %o0, move it to %i0

	ret			! Return from subroutine
	restore			! Restore caller's window; in "ret" delay slot



