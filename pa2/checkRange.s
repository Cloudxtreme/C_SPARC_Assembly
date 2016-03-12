/* Filename: checkRange.s 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: SPARC assembly routine to check if the third argument
 * 		is within min and offset+min range (1st and 2nd arguments),
 * 		and also checks to see offset (2nd argument) is positive.
 * Date: 1/19/2016
 * Sources of Help: PA1 Handout, Lecture #4 Notes, PA1 Discussion Slides
 */

	.global checkRange	! Declares the symbol to be globally visible so
				! we can call this function from other modules.

	.section ".text"	! The text segment begins here


/*
 * Function name: checkRange()
 * Function prototype: 
 * 	long checkRange( long minRange, long offset, long value );
 * Description: Checks to see if value is within range of minRange
 * 		and minRange+offset, inclusive. Also checks to see if 
 * 		offset is not negative
 * Parameters:
 * 	arg 1: long minRange -- minimum range to be checked - lower limit
 * 	arg 2: long offset   -- offset+minRange - upper limit
 * 	arg 3: long value    -- number for which we are checking range
 * Side Effects: None
 * Error Conditions: None
 * Return Value: 0 if the value is not within range
 * 		 1 if the value is within range
 * 		 -1 if the offset is negative (error)
 * *
 * Registers Used:
 *  	%i0 - arg 1 -- minRange
 *  	%i1 - arg 2 -- offset
 *  	%i2 - arg 3 -- value
 */  	

checkRange:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was 
				! calculated
	
	mov	%i1, %o0	! Copy arg 2 (offset) to %o0 so we can 
	call	isNegative	! call isNegative function and get return
	nop			! value

	cmp	%o0, 0		! Check to see if return value from isNegative
	bne	else1		! is not equal to one (not negative)
	nop

	add	%i0, %i1, %l0	! Add minRange and offset to get upper limit
				! and store in %l0; will be needed for check

	cmp	%i0, %i2	! Compare minRange and value, if minRange
	bg	else2		! larger than value, then go to else2
	nop
	
	cmp 	%l0, %i2	! Compare minRange+offset and value, if
	bl	else2		! minRange+offset is less than value, then
	nop			! go to else2
	
	ba	else3		! Comaprison check passed, value is within
	nop			! range, go to else3

else1:				! Return value from isNegative was 1, meaning
	clr	%i0		! the offset was negative, so we will return 
	mov	-1, %i0		! -1 from this function by setting %i0 to -1
	ba	end_if		! Now go to end_if
	nop

else2:				! Since check of range failed, we clear %i0
	clr	%i0		! and set it to 0 so it can be returned
	mov 	0, %i0		
	ba	end_if		! Now go to end_if
	nop

else3:				! Since comparsion checks have passed, we 
	clr 	%i0		! clear %i0 and set it to 1 so it can be
	mov	1, %i0		! returned
	ba	end_if		! Not go to end_if
	nop

end_if:
	ret			! Return from subroutine
	restore			! Restore caller's window; in "ret" delay slot
