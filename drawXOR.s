/*
 * Filename: drawXOR.s
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Draws the xor pattern
 * 		Called from main() in pa1.c
 * Date: 1/24/2016
 * Sources of Help: PA1 Assignment Handout, Lecture #4 Notes, 
 * 		    PA1 Discussion Slides pt.2
 */

	.global drawXOR		! Declares the symbol to be globally visible
				! so we can call this function from other
				! modules

	.section ".text"	! The text segment begins here

NEWLINE = 0x0A

/*
 * Function name: drawXOR()
 * Function prototype: void drawXOR( char xorChar, int width, int speed );
 * Description: The function performs the actul outputting of the individual 
 * 		xor characters.
 * 		Called from main() in pa1.c
 * Parameters:
 * 	arg 1 - char xorChar -- xor character to be printed in pattern
 * 	arg 2 - int width    -- width of line in pattern to be printed
 * 	arg 3 - int speed    -- speed that will be used for usleep()
 *
 * Side Effects: Prints out the whole patter of xor'ing characters
 * Error Conditions: None. Error input checking done in main()
 * Return Values: None
 *
 * Registers Used:
 * 	%i0 - arg 1 -- char xorChar
 * 	%i1 - arg 2 -- int width
 * 	%i2 - arg 3 -- int speed 
 *
 * 	%l0 -- outerloop_count -- int j
 * 	%l1 -- innerloop_count -- int i
 *	%l2 -- outerloop_upperbound var -- (width*2-1)
 *	%l3 -- innerloop first conditional var -- (i-1)
 *	%l4 -- innerloop second conditional var -- (width-1)
 *	%l5 -- innerloop third conditional var -- (j-width+1)
 *	%l6 -- innerloop fourth conditional var -- (width-1-i)
 */

drawXOR:
	save	%sp, -96, %sp	! Save the caller's window; if different than 
				! -96, then comment on how that value was 
				! calculated

	clr	%l0		! set j = 0
	clr 	%l1		! set i = 0
	clr 	%l2		! set outerloop_upperbound var = 0
	clr	%l3		! set innerloop 1st conditional var = 0	
	clr	%l4		! set innerloop 2nd conditional var = 0
	clr	%l5		! set innerloop 3rd conditional var = 0
	clr	%l6		! set innerloop 4th conditional var = 0

	mov	%i1, %l2	! Copy value of width to %l2, will be used for
				! upperbound for outerloop
	add	%l2, %l2, %l2	! Multiply %l2 by 2 (=%l2+%l2) 
	dec	%l2		! %l2 (outerloop_upperbound) and decrement by 1

	cmp	%l0, %l2	! j < (width*2-1) -- outerloop_upperbound 
	bge	endouterfor
	nop
	
outerfor:
	mov 	%i1, %l1	! Reset i = 0

	cmp	%l1, 0		! Check to see if i > 0, if i is less than or
	ble	endinnerfor	! or equal to zero then branch to endinnerfor
	nop

!	clr	%o0		! Clear %o0 output register
!	mov	%i2, %o0	! Copy sleep value to %o0
!	call	usleep		! Call usleep to sleep for sleep value
!	nop

!	clr	%o0		! Clear %o0 output register
!	mov 	NEWLINE, %o0	! Copy newline char to %o0
!	call 	printChar	! Call printChar to print newline char
!	nop

innerfor:
	clr	%l3		! Clear %l3 (innerloop 1st conditional) when
				! entering the innerfor branch

	sub	%l1, 1, %l3	! Set %l3 = i-1

	cmp	%l3, %l0	! Compare: (i-1) > j, if true then goto else1	
	bg	else1		! otherwise continue 
	nop

	mov	%i0, %o0	! Since (i-1)<=j then call line function
	mov	%l3, %o1	! line(xorChar, i-1, width)
	mov	%i1, %o2
	call 	line
	nop

	ba	endif1		! Always branch to endif1 here skipping over
	nop			! else1 branch

else1:	
	mov	%i0, %o0	! Since (i-1) > j, then call line line function
	mov	-1, %o1		! as such:
	mov	%i1, %o2	! line(xorChar, -1, width)
	call	line
	nop

endif1:				! Come to this branch after innerfor or else1
				! always
	clr	%l4		! Clear innerloop 2nd conditional: (width-1)
	clr	%l5		! Clear innerloop 3rd conditional: (j-width-1)
	clr 	%l6		! Clear innerloop 4th conditional: (width-1-i)

	sub	%i1, 1, %l4	! Calculate innerloop 2nd conditional 

	cmp 	%l0, %l4	! Compare: j<=(width-1), if true then goto 
	ble	endif2		! endif2, otherwise continue
	nop
	
	cmp	%l1, %i1	! Compare: i = width, if true then goto endif2
	be	endif2		! otherwise continue
	nop
	
	cmp	%i1, %l1	! Compare: width<=i, if true then goto endif2
	ble	endif2		! otherwise continue
	nop

	sub	%l0, %i1, %l5	! Calculate innerloop 3rd conditional
	inc	%l5		 

	sub	%i1, 1, %l6	! Calculate innerloop 4th conditional
	sub	%l6, %l1, %l6

	cmp	%l5, %l6	! Compare: (j-width+1)<=(width-1-i), if true
	ble	endif2		! then goto endif2, otherwise continue
	nop

	mov	%i0, %o0	! Since all the compares in innerloop
	mov	%l6, %o1	! conditionals 2, 3, and 4 were false, then we
	mov	%i1, %o2	! will call line as such:
	call	line		! line(xorChar, width-1-i, width)
	nop	

endif2:
	mov	NEWLINE, %o0	! Print newline char at end of innerloop
	call	printChar
	nop
	
	dec	%l1		! Decrement i: i--

	cmp	%l1, 0		! Comapre: if i>0 then continue innerfor loop
	bg	innerfor	! otherwise continue
	nop

endinnerfor:
	mov 	%i2, %o0	! After the innerfor loop has ended, we want 
	call	usleep		! to call usleep function, passing in sleep
	nop			! parameter

	mov	NEWLINE, %o0	! Print newline char so each line has a new 
	call 	printChar	! frame
	nop

	inc	%l0		! Increment j: j++

	cmp	%l0, %l2	! Comapre: if j<(width*2-1) then continue 
	bl 	outerfor	! outerfor loop, otherwise continue to 
	nop			! endouterfor branch

endouterfor:
	ret			! Return from subroutine
	restore			! Restore caller's window; in "ret" delay slot

