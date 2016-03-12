/*
 * Filename: line.s
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Prints out one line of characters. 
 * 		Called from drawXOR()
 * Date: 1/24/2016
 * Sources of help: PA1 Assignment Sheet, PA1 Discussion Slides Pt.2
 * 		    Lecture #4 Notes
 */

	.global line		! Decalres the symbol to be globally visible
				! so we can call this function from other 
				! modules

	.section ".text"	! The text segment begins here

SPACE = 0x20			! Define constant for space character

/*
 * Function name: line()
 * Function prototype: void line( char xorChar, long charpos, long width );
 * Description: Prints out the XOR character at position charpos, and will fill
 * 		in the rest of the spaces via calls to printChar(). Line will
 * 		be as long as value of width.
 * 		Called from drawXOR().
 * Parameters: 
 * 	arg 1 -- char xorChar -- xorChar to be printed at position charpos
 * 	arg 2 -- long charpos -- postion where xorChar to be printed
 * 	arg 3 -- long width   -- width of line to printed
 *	
 * Side Effects: Prints out a line of characters, with xorChar at charpos, in
 * 		 a line that is width long.
 * Error Conditions: If charpos is less than zero or greater than or equal to
 * 		     to width, then all spaces will be printed in the line.
 * Return Values: None
 *
 * Registers Used:
 *	%i0  - arg 1 -- char xorChar, char to be printed
 *	%i1  - arg 2 -- long charpos, postion of xorChar
 *	%i2  - arg 3 -- long width, length of line to be printed
 *	
 *	%l0  - loopcount -- holds count for the loop
 */

line:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was 
				! calculated
	
	clr 	%l0		! Clear %l0, will hold count for the loop

	cmp	%l0, %i2	! Check to see if loopcount is not greater
	bge	endloop		! than width, otherwise goto endloop
	nop
	
	cmp	%i1, 0		! If charpos is less than zero, then goto
	bl	loop		! to loop and print spaces
	nop
	
	cmp	%i1, %i2	! If charpos is greater than or equal to 
	bge	loop		! width then goto loop and print spaces
	nop

	ba 	loop		! Always branch to loop here, skipping
	nop			! printchar branch

printchar:			! This branch is called from loop when 
	mov	%i0, %o0	! xorChar needs to be printed at charpos
	call 	printChar
	nop
	
	inc	%l0		! Increment loopcount so that when enter
				! loop branch below, loopcount and charpos
				! wont still have same value, causing endless
				! loop
	
loop:				! Loop to print spaces for a line that is 
				! long as width, and print xorChar at charpos
				
	cmp	%i1, %l0	! If charpos has same value as loopcount then
	be	printchar	! branch up to printchar and print xorChar 
	nop			! is at charpos position currently

	mov	SPACE, %o0	! Copy space char to output register %o0,
	call 	printChar	! Call printChar function to print space char
	nop
	
	inc	%l0		! Increment loopcount

	cmp	%l0, %i2	! If loopcount is less than width value then 
	bl	loop		! continue loop or go to endloop below
	nop

endloop:			! End of for-loop
	ret			! Return from subroutine
	restore			! Restore caller's window; in "ret" delay slot
