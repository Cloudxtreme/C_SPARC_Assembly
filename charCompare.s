/*
 * Filename: charCompare.s  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Compares two characters
 * Date: 2/15/16
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.1
 */

	.global charCompare	! Declares the symbol to be globally visible so
				! we can call this function from other modules

	.section ".text"	! The text segment begins here.

/*
 * Function name: charCompare() 
 *
 * Function prototype: int charCompare( const void *p1, const void *p2 );
 *
 * Description: Compares two characters passed in as arguments 
 *              NOTE: This is a leaf subroutine
 *          
 * Parameters: 
 *      arg 1 - const void *p1 - first character argument
 *      arg 2 - const void *p2 - second character argument
 *              
 * Side Effects: None
 *
 * Return Values: -1 -- if 2nd char is greater than 1st
 * 		   0 -- if both chars are equal
 * 		   1 -- if 1st char is greater than 2nd
 *
 * Registers Used: 
 * 	%o0 - arg1 - const void *p1
 * 	%o1 - arg2 - const void *p2

charCompare:

	ldub	[%o0], %o0
	ldub	[%o1]. %o1

	cmp	%o0, %o1
	be	else1
	nop

	cmp 	%o0, %o1
	bl	else2
	nop
	
	mov 	1, %o0
	ba 	endif
	nop
	
else1:
	mov 	0, %o0
	ba 	endif
	nop

else2:
	mov	-1, %o0
	ba 	endif
	nop

endif:
	retl
	nop
	

