/* Filename: isNegative.s 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: SPARC assembly routine to check if the argument
 * 		(offset value) is negative. 
 * Date: 1/19/2016
 * Sources of Help: PA1 Handout, Lecture #4 Notes
 */

	.global isNegative	! Declares the symbol to be globally visible so
				! we can call this function from other modules.

	.section ".text"	! The text segment begins here


/*
 * Function name: isNegative()
 * Function prototype: long isNegative( long num );
 * Description: Checks to see if argument (long num) is negative
 * Parameters:
 * 	arg 1: long num -- number to be checked if it is negative
 *
 * Side Effects: None
 * Error Conditions: None
 *  Return Value: 1 if the number is negative, 0 otherwise
 *
 * Registers Used:
 *  	%i0 - arg 1 -- number to be checked if negative or not
 */

isNegative:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was 
				! calculated

	cmp	%i0, 0		! Comapre paramter with 0
	bge	else		! opposite logic to branch over if statement
	nop

	clr 	%i0		! Clear the %i0 register
	mov   	1, %i0		! If statement - %i0 is less than 0,
	ba 	end_if		! parameter is negative
	nop

else:	
	clr	%i0		! Clear the %i0 register
	mov 	0, %i0		! Else statment - %i0 is greater than or
				! equal to 0, therefore parameter is positive

end_if:				! After if-else statement
	ret			! return from subroutine
	restore			! Restore caller's window; in "ret" delay slot

