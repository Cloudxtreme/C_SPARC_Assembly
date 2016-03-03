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
	
	mov	%i0, %l1	! Copy ptr to string 1 to %l1
	mov 	%i1, %l2	! Copy ptr to string 2 to %l2
	mov	%i2, %l0	! Copy length n to %l0
	
	cmp 	%l0, 0		! Check to see if n is not zero, otherwise
	be	equal		! go to equal. Value of 0 for n, should 
	nop			! never be passed in to this function since it
			 	! doesn't make any sense to do so, however this
				! mimics strncmp function

loop:
	dec 	%l0		! Decrement n, need this to keep track up to 
				! what character index in string we will check
				! upto

	ldub	[%l1], %l3	! Load the first character of string 1 into %l3	
	mov	%l3, %o0	! then make it lowercase by calling tolower()
	call 	tolower
	nop
	mov	%o0, %l3

	ldub	[%l2], %l4	! Load the first character of string 2 into %l4
	mov	%l4, %o0	! then make it lowercase by calling tolower()
	call	tolower
	nop
	mov	%o0, %l4

	cmp	%l3, %l4	! If both the chars from string 1 and 2 are
	be	endif		! equal then branch to endif always
	nop

	cmp	%l0, 0		! Check to see if n = 0, if so then branch to
	be	checkChars	! checkChars always
	nop

	cmp	%l3, 0		! Check to see if char from string 1 isn't a 
	be	checkChars	! null char, if it is then branch to checkChars
	nop			! always

	cmp	%l4, 0		! Check to see if char from string 2 isn't a 
	be	checkChars	! null char, if it is then branch to checkChars
	nop			! always

	ba	checkChars	! Always brach to checkChars here; just to not
	nop			! continue to endif (not like it would happen)

endif:
	inc	%l1		! Increment the ptr to next char in string 1
	inc	%l2		! Increment the ptr to next char in string 2

	cmp	%l0, 0		! Check to see the n != 0, if it isnt, then
	bne	loop		! continue looping
	nop

checkChars:
	sub	%l3, %l4, %l5	! Subtract the char value of string 2 from char
				! value of string 1, store that value into %l5

	cmp	%l5, 0		! Check to see is subtraction value is greater
	bg	positive 	! than zero, if so then branch to positive
	nop
	
	cmp	%l5, 0		! Check to see if subtraction values is less
	bl	negative	! than zero, if so then branch to negative
	nop

	ba	equal		! Since it is not greater or less than zero, it
	nop			! must be equal to zero, so branch to equal

positive:
	mov 	1, %i0		! Since string 1 char was greater than string 2
	ba	endloop		! char, move 1 to %i0 so we can return this 
	nop			! value, then branch to endloop

negative:
	mov	-1, %i0		! Since string 1 char was less than string 2	
	ba 	endloop		! char, move -1 to %i0 so we can return this 
	nop			! value, then branch to endloop
	
equal:
	mov	0, %i0		! Since nth char of string 1 and 2  is equal, 
				! move 0 to %i0 so we can return this value
				! then continue to endloop

endloop:
	ret			! Return from subroutine
	restore			! Restore caller's window; in ret's delay slot


