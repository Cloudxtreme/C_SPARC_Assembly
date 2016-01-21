/* Filename: isOdd.s 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: SPARC assembly routine to check if the argument
 * 		(width value) is odd or not. 
 * Date: 1/19/2016
 * Sources of Help: PA1 Handout
 */

	.global isOdd		! Declares the symbol to be globally visible so
				! we can call this function from other modules.

	.section ".text"	! The text segment begins here


/*
 * Function name: isOdd()
 * Function prototype: long isOdd( long num );
 * Description: Checks to see if argument (long num) is odd
 * Parameters:
 * 	arg 1: long num -- number to be checked if it is odd
 *
 * Side Effects: None
 * Error Conditions: None
 * Return Value: 1 if the number is odd, 0 otherwise
 *
 * Registers Used:
 *  	%i0 - arg 1 -- number to be checked if odd or not
 */

isOdd:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was
				! calculated
	
	mov 	%i0, %o0	! Put a copy of the parameter in the register
				! %o0 which is to be used by .rem

	mov	2, %o1		! Put constant value of 2 in the register
				! %o1 which is also to be used by .rem.
				! .rem return value will be in %o0

	call	.rem		! This is a transfer ofcontrol instruction
	nop			! must be followed by nop. Calling remainder
				! subroutine.
	
	cmp	%o0, 0		! Compare if .rem subroutine return value
				! is 0;
	bne	else		! opposite logic to brach over if statement 
	nop

	mov	1, %i0		! if statement - remainder was 0, so copy
	ba	endif		! value of 1 to %i0, so value of 1 will be
	nop			! returned from this function

else:
	mov	0, %i0		! else statment - remainder was not 0, so copy
				! value of 0 to %i0, so value of 0 will be 
endif:				! returned from this function
	ret			! Return from subroutine
	restore			! Restore caller's window; in "ret" delay slot
