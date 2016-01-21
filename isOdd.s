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
	
	and 	%i0, 1, %o0	! And the parameter with 1 and store in %o0

	
	cmp	%o0, 1 		! Compare if %o0 is equal to 1 or not
	bne	else		! opposite logic to brach over if statement 
	nop

	clr	%i0		! Clear %i0 register
	mov	1, %i0		! if statement - %i0 is equal to 1, parameter 
	ba	end_if		! therfore is odd.
	nop			

else:
	clr 	%i0		! Clear %i0 register
	mov	0, %i0		! else statment - %i0 is not equal to 1, 
				! therefore parameter is even 

end_if:				! After if-else statement
	ret			! Return from subroutine
	restore			! Restore caller's window; in "ret" delay slot
