/*
 * Filename: converToBCD.s
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Converts decimal clock array to BCD format, used in displaying 
 * Date: 2/3/2016
 * Sources of help: PA2 Assignment Sheet, PA2 Discussion Slides Pt.1
 * 		    Lecture #6 Notes
 */

	.global convertToBCD	! Decalres the symbol to be globally visible
				! so we can call this function from other 
				! modules

	.section ".text"	! The text segment begins here

LSHIFT = 4			! Constant to hold left shift byte value
TEN = 10			! Constant to hold divide and modulus val

HRS_IDX_LONG = 0		! Constant to hold hours long array byte offset
MIN_IDX_LONG = 4		! Constant to hold mins long array byte offset
SEC_IDX_LONG = 8		! Constant to hold secs long array byte offset

HRS_IDX_CHAR = 0		! Constant to hold hours char array byte offset
MIN_IDX_CHAR = 1		! Constant to hold mins char array byte offset
SEC_IDX_CHAR = 2		! Constant to hold secs char array byte offset

/*
 * Function name: convertToBCD()
 *
 * Function prototype: 
 * 	void convertToBCD(const long clockDecimal[], unsigned char clockBCD[]);
 * 
 * Description: Convert decimal clock array into BCD format, by expanding
 * 		each value for hours, mins, and secs, into two nibbles,
 * 		so that each byte can be represented by two hex digits,
 * 		reflecting the decimal value of the time. Hex digits
 * 		are made using bit shifts and oring two nibbles together
 * 		to get desired value
 
 * Parameters: 
 * 	arg 1 -- const long clockDecimal[] -- array where time is
 * 	arg 2 -- unsigned char clockBCD[] -- where we will store hex BCD time
 *	
 * Side Effects: Converts decimal clock values into BCD, and stores them
 * 		 as hex digits into unsigned char clockBCD[]. 
 * 		 
 * Error Conditions: None 
 * 		   
 * Return Values: None
 *
 * Registers Used:
 *	%i0 - arg 1 -- const long clockDecimal[]
 *	%i1 - arg 2 -- unsigned char clockBCD[]
 *
 *	%l0 -- holds value of hours from clockDecimal
 *	%l1 -- holds value of mins from clockDecimal
 *	%l2 -- holds value of secs from clockDecimal
 *	%l3 -- holds BCD hours
 *	%l4 -- holds BCD mins
 *	%l5 -- holds BCD secs
 */

convertToBCD:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was 
				! calculated
	
	clr	%l0		! Clear contents of %l0
	clr	%l1		! Clear contents of %l1
	clr	%l2		! Clear contents of %l2
	clr	%l3		! Clear contents of %l3
	clr	%l4		! Clear contents of %l4
	clr	%l5		! Clear Contents of %l5

	ld	[%i0+HRS_IDX_LONG], %l0	! Load hours from clockDecimal into %l0
	ld	[%i0+MIN_IDX_LONG], %l1	! Load mins from clockDecimal into %l1
	ld	[%i0+SEC_IDX_LONG], %l2	! Load secs from clockDecimal into %l2

	mov 	%l0, %o0	! Put copy of decimal hours into %o0
	mov	TEN, %o1	! Put copy of 10 into %o1
	call	.div		! Divide hours by ten
	nop

	mov	%o0, %l3		! Put division result into %l3
	sll	%l3, LSHIFT, %l3	! Shift %l3 by 4 bits left 

	mov 	%l0, %o0	! Put copy of decimal hours into %o0		
	mov	TEN, %o1	! Put copy of 1 into %o1
	call 	.rem		! Find remainder of (hours/10)
	nop

	or	%l3, %o0, %l3		! Or two nibbles to get hours hex byte
	stb	%l3, [%i1+HRS_IDX_CHAR]	! Store hours hex byte into clockBCD

	mov 	%l1, %o0	! Put copy of decimal mins into %o0
	mov	TEN, %o1	! Put copy of 10 into %01
	call	.div		! Divide mins by 10
	nop

	mov	%o0, %l4		! Put division result into %l4
	sll	%l4, LSHIFT, %l4	! Shift %l4 buy 4 bits left

	mov 	%l1, %o0	! Put copy of decimal mins into %o0
	mov	TEN, %o1	! Put copy of 10 into %o1
	call 	.rem		! Find remainder of (mins/10)
	nop

	or	%l4, %o0, %l4		! Or two nibbles to get mins hex byte
	stb	%l4, [%i1+MIN_IDX_CHAR]	! Store mins hex byte into clockBCD

	mov 	%l2, %o0	! Put copy of decimal secs into %o0
	mov	TEN, %o1	! Put copy of 10 into %01
	call	.div		! Divide secs by 10
	nop

	mov	%o0, %l5		! Put division result into %l5
	sll	%l5, LSHIFT, %l5	! Shift %l5 by 4 bits left

	mov 	%l2, %o0 	! Put copy of decimal secs into %o0
	mov	TEN, %o1	! Put copy of 10 into %o1
	call 	.rem		! Find remainder of (secs/10)
	nop

	or	%l5, %o0, %l5		! Or two nibbles to get secs hex byte
	stb	%l5, [%i1+SEC_IDX_CHAR]	! Store secs hex byte into clockBCD

	ret			! Return from subroutine
	restore			! Restore caller's window; in "ret" delay slot
