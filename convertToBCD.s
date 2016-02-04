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

LSHIFT = 4
TEN = 10

HRS_IDX_LONG = 0
MIN_IDX_LONG = 4
SEC_IDX_LONG = 8

HRS_IDX_CHAR = 0
MIN_IDX_CHAR = 1
SEC_IDX_CHAR = 2

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
	
	clr	%l0
	clr	%l1
	clr	%l2
	clr	%l3
	clr	%l4
	clr	%l5

	ld	[%i0+HRS_IDX_LONG], %l0	! Load hours from clockDecimal into %l0
	ld	[%i0+MIN_IDX_LONG], %l1	! Load mins from clockDecimal into %l1
	ld	[%i0+SEC_IDX_LONG], %l2	! Load secs from clockDecimal into %l2

	mov 	%l0, %o0
	mov	TEN, %o1
	call	.div
	nop

	mov	%o0, %l3
	sll	%l3, LSHIFT, %l3

	mov 	%l0, %o0
	mov	TEN, %o1
	call 	.rem
	nop

	or	%l3, %o0, %l3
	stb	%l3, [%i1+HRS_IDX_CHAR]

	mov 	%l1, %o0
	mov	TEN, %o1
	call	.div
	nop

	mov	%o0, %l4
	sll	%l4, LSHIFT, %l4

	mov 	%l1, %o0
	mov	TEN, %o1
	call 	.rem
	nop

	or	%l4, %o0, %l4
	stb	%l4, [%i1+MIN_IDX_CHAR]

	mov 	%l2, %o0
	mov	TEN, %o1
	call	.div
	nop

	mov	%o0, %l5
	sll	%l5, LSHIFT, %l5

	mov 	%l2, %o0
	mov	TEN, %o1
	call 	.rem
	nop

	or	%l5, %o0, %l5
	stb	%l5, [%i1+SEC_IDX_CHAR]

	ret
	restore
