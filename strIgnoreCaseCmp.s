/*
 * Filename: strIgnoreCaseCmp.s 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Compares two strings character by character up to n characters
 * 		ignoreing case.
 * Date: 3/2/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.1
 */

	.global strIgnoreCaseCmp 	! Declare the symbol to be globally
					! visible, so we can call this function
					! from other modules

	.section ".text"		! The text segment begins here

/*
 * Function name: strIgnoreCaseCmp()
 *	
 * Function prototype: 
 *  	int strIgnoreCaseCmp( const char *s1, const char *s2 unsigned int n) ;
 *
 * Description: Compares two strings char by char up to n chars ignoring case.
 * 		Uses tolower() to make each character all lower case when 
 * 		doing comparison
 *          
 * Parameters: 
 *      arg 1 - const char *s1 -- string to be compared
 *      arg 2 - const char *s2 -- string to be compared
 *      arg 3 - unsigned int n -- index of string up to where comparison needs
 *      			  to be done
 *
 * Side Effects: Just compares two strings up till n characters
 * 
 * Error Conditions: None
 *
 * Return Values: 
 *     -1 - if the second string is greater (up till nth char)
 *      0 - if both strings are equal (up till nth char)
 * 	1 - if the first string is greater (up till nth char)
 *
 * Registers Used: 
 * 	
 * 	%i0 - const char *s1 - string 1
 * 	%i1 - const char *s2 - string 2
 * 	%i2 - unsigned int n - index to compare up to
 * 
 *	%l0 - copy of %i2 -- unsigned int n
 *	%l1 - copy of %i0 -- string 1
 *	%l2 - copy of %i1 -- string 2
 *	%l3 - converted lowercase char from string 1
 *	%l4 - converted lowercase char from string 2
 *	%l5 - holds
 */

strIgnoreCaseCmp:
	save	 %sp, -96, %sp	! Save the caller's window; if differen than 
				! -96, then comment on how that value was 
				! calculated.
	
	mov	%i0, %l1
	mov 	%i1, %l2
	mov	%i2, %l0
	
	cmp 	%l0, 0
	be	endloop
	nop

loop:
	dec 	%l0
	
	ldub	[%l1], %l3
	mov	%l3, %o0
	call 	tolower
	nop
	mov	%o0, %l3

	ldub	[%l2], %l4
	mov	%l4, %o0
	call	tolower
	nop
	mov	%o0, %l4

	cmp	%l3, %l4
	be	endif
	nop

endif:
	inc	%l1
	inc	%l2

	cmp	%l0, 0
	bne	loop
	nop

checkChars:
	sub	%l3, %l4, %l5
	
	cmp	%l5, 0
	bg	positive 
	nop
	
	cmp	%l5, 0
	bl	negative
	nop

	ba	equal
	nop

positive:
	mov 	1, %i0
	ba	endloop
	nop

negative:
	mov	-1, %i0
	ba 	endloop
	nop
	
equal:
	mov	0, %i0
	ba 	endloop
	nop


endloop:
	ret	
	restore


