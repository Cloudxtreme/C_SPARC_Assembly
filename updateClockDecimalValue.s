/*
 * Filename: updateClockDecimalValue.s
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Updates the decimal value of the clock based on the amount to 
 * 		increment by.
 * Date: 2/3/2016
 * Sources of help: PA2 Assignment Sheet, PA2 Discussion Slides Pt.1
 * 		    Lecture #6 Notes
 */

	.global updateClockDecimalValue
				! Decalres the symbol to be globally visible
				! so we can call this function from other 
				! modules

	.section ".text"	! The text segment begins here

/*
 * Function name: updateClockDecimalValue()
 *
 * Function prototype: 
 * 	long updateClockDecimalValue( long * clockVal, long updateAmt, 
 * 				      long maxVal );
 *
 * Description: Using the pointer given to this function, *clockVal, be it
 * 		either hours, mins, or secs, it will update the respective
 * 		value by an amoount, updateAmt. If updated value is over the
 * 		max value, maxVal, then the function will return this carry 
 * 		out, and save the remainder. 
 * 	
 * Parameters: 
 * 	arg 1 -- long * clockVal -- pointer to current hours, mins, or secs
 * 				    (from clockDecimal array)
 * 	arg 2 -- long updateAmt  -- amount to add to current clockVal
 * 	arg 3 -- long maxVal     -- maximum value of current unit 
 * 				    (hours, mins, or secs)
 *	
 * Side Effects: Updates the decimal Clock by amount passed in, and 
 * 		 keeps track of carry out and remainders
 * 		 
 * Error Conditions: None
 * 		     
 * Return Values: Carryout of addition - excess amount, if overflows over 
 * 		  maxVal
 *
 * Registers Used:
 *	%i0  - arg 1 -- long * clockVal
 *	%i1  - arg 2 -- long updateAmt
 *	%i2  - arg 3 -- long maxVal
 *	
 *	%l0  -- holds value of of what *clockVal is pointing to
 *i	%l1  -- copy of %l0
 */

updateClockDecimalValue:	
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was
				! calculated

	clr	%l0		! Clear contents of %l0
	clr	%l1		! Clear contents of %l1

	ld	[%i0], %l0	! Get the value stored in pointer *clockVal,
				! pointer address is in %i0
	add	%l0, %i1, %l0	! Add value that clockVal is pointing to, to
				! updateAmt

	cmp	%l0, %i2	! Compare (clockVal value + updateAmt) with 
	bge	else		! maxVal, if greater than go to else, otherwise
	nop			! continue

	st	%l0, [%i0]	! Since (clockVal value + updateAmt) was less
	mov	0, %i0		! than maxVal, store this sum back into where 
	ba	endif		! clockVal pointer was pointing to. Store 0
	nop			! into %i0 so 0 will be returned from this
				! from this function, then go to endif

else:

	mov	%l0, %l1	! Make a copy of %l0, store copy in %l1
								
	mov 	%l0, %o0	! Since (clockVal value + updateAmt) was
	mov 	%i2, %o1	! bigger than maxVal, we will get remainder
	call 	.rem		! (clockVal value + updateAmt) % maxVal
	nop

	mov 	%o0, %l0	! Store the remainder from above, back into
	st	%l0, [%i0]	! where the pointer clockVal was pointing to
	
	cmp	%l1, %i2	! If (clockVal value + updateAmt) is equal to
	be	else1		! maxVal, then go to else1
	nop
	
	mov	%l1, %o0	! Since (clockVal value + updateAmt) was not
	mov	%i2, %o1	! equal to maxVal (after addition from line 62)
	call 	.div		! Find: (clockVal value + updateAmt)/maxVal
	nop

	mov 	%o0, %i0	! Store result of division from above into %i0
	ba	endif		! so that value will be returned from this
	nop			! function.

else1:	
	mov 	0, %i0		! Since after addition of line 62, 
				! (clockVal value + updateAmt) was same as 
				! maxVal, we want carry over to be zero, so 
				! move 0 to %i0, so 0 will be returned.
endif:
	ret			! Return from subroutine
	restore			! Restore caller's window; in "ret" delay slot
	
	
