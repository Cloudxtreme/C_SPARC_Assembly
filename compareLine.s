/*
 * Filename: comapreLine.s 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Compares the two lines members of the struct uniq
 * Date: 3/5/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.2
 */

	.global compareLine	! Decalre the symbol to be globally visible,
				! so we can call this function from other 
				! modules

	.section ".text"	! The text segment begins here

/*
 * Function name: compareLine()
 *
 * Function prototype: int compareLine( const void *p1, const void *p2 );
 *  
 * Description: Compares the line members of two struct uniq's. First calculate
 * 		the offset of the line member in a struct uniq (done in 
 * 		pa4Globals.c). Then load the line members from the base plus 
 * 		the offset. Then compare the two lines using strcmp.
 *          
 * Parameters: 
 *      arg 1 - const void *p1 -- first struct
 *      arg 2 - const void *p2 -- second struct 
 *
 * Side Effects: Determine which line member of each uniq struct is greater,
 * 		 lesser, or equal
 * 
 * Error Conditions: None
 *
 * Return Values: 
 * 	-1 - if the line member of the second struct uniq is greater
 * 	 0 - if the line members of both structs are equal
 * 	 1 - if the line member of the first struct is greater	 
 * 		
 *
 * Registers Used: 
 * 	%i0 - pointer to first uniq struct
 * 	%i1 - pointer to second uniq struct
 *
 * 	%l0 - holds the value for line member offset in struct uniq
 * 	%l1 - holds the value of first uniq struct line member
 * 	%l2 - holds the value of the second uniq struct line member
 * 	%l3 - holds the return value from strcmp() on the two lines
 */

compareLine:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was
				! calculated

	/* Clear the local registers */
	clr 	%l0
	clr 	%l1
	clr	%l2

	/* Grab the value of the line member offset of struct uniq from
	 * pa4Globals.c, and store in %l0
	 */
	set	UniqLineOffset, %l0
	ld	[%l0], %l0

	add	%l0, %i0, %l1	! Add line offset to first uniq struct to get
	ld	[%l1], %l1	! the correct address, then load the value into
				! %l1

	add	%l0, %i1, %l2	! Add kube iffset ti second uniq struct to get
	ld	[%l2], %l2	! the correct addressm then load the value into
				! %l2

	mov	%l1, %o0	! Copy the line of 1st struct to %o0
	mov	%l2, %o1	! Copy the line of 2nd struct to %o1

	call	strcmp		! Compare the two lines by calling the strcmp()
	nop			! function

	mov 	%o0, %l3	! Copy the return value from strcmp() into %l3

	cmp 	%l3, 0		! If return value from strcmp() is equal to 0, 
	be	equal		! then branch to equal
	nop

	cmp 	%l3, 0		! If return value from strcmp() is less than 0,
	bl	negative	! then branch to negative
	nop

	mov	1, %i0		! Since return value from strcmp() is not equal 
	ba	endif		! to 0 or less than 0, then it must be greater
	nop			! than 0. So move 1 to %i0, so we can return 1
				! from this function and branch to endif always

equal:
	mov	0, %i0		! Since return value from strcmp() was 0, then
	ba 	endif		! lines are equal. Move 0 to %i0, so we can 
	nop			! return 0 from this function and branch to 	
				! endif always

negative:
	mov 	-1, %i0		! Since return value from strcmp() is less than
				! 0, then move -1 to %i0, so we can return -1 
				! from this function and continue below to 
				! endif

endif:	
	ret			! Return from subroutine	
	restore			! Restore caller's window; in ret's delay slot
