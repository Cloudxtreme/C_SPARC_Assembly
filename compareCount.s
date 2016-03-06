/*
 * Filename: comapreCount.s 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Compares the two count members of the struct uniq
 * Date: 3/5/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.2
 */

	.global compareCount	! Decalre the symbol to be globally visible,
				! so we can call this function from other 
				! modules

	.section ".text"	! The text segment begins here

/*
 * Function name: compareCount()
 *
 * Function prototype: int compareCount( const void *p1, const void *p2 );
 *  
 * Description: Compares the count members of two struct uniqs. First calculate
 * 		the offset of the count member in a struct uniq (done in 
 * 		pa4Globals.c). Then load the count members from the base plus 
 * 		the offset. Then compare the two count's.
 *          
 * Parameters: 
 *      arg 1 - const void *p1 -- first struct
 *      arg 2 - const void *p2 -- second struct 
 *
 * Side Effects: Determine which count member of each uniq struct is greater,
 * 		 lesser, or equal
 * 
 * Error Conditions: None
 *
 * Return Values: 
 * 	-1 - if the count member of the second struct uniq is greater
 * 	 0 - if the count members of both structs are equal
 * 	 1 - if the count member of the first struct is greater	 
 *
 * Registers Used: 
 * 	%i0 - pointer to first uniq struct
 * 	%i1 - pointer to second uniq struct
 *
 * 	%l0 - holds the value for count member offset in struct uniq
 * 	%l1 - holds the value of first uniq struct count member
 * 	%l2 - holds the value of the second uniq struct count member
 */

compareCount:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was
				! calculated

	/* Clear the local registers */
	clr 	%l0
	clr 	%l1
	clr	%l2

	/* Grab the value of the count member offset of struct uniq from
	 * pa4Globals.c, and store in %l0
	 */
	set	UniqCountOffset, %l0
	ld	[%l0], %l0

	add	%l0, %i0, %l1	! Add count offset to 1st uniq struct to get 
	ld	[%l1], %l1	! the correct address, then load value back
				! into %l1

	add	%l0, %i1, %l2	! Add count offset to 2nd uniq struct to get 
	ld	[%l2], %l2	! the correct address, then load value back 
				! into %l2

	cmp	%l2, %l3	! If count of both uniq struct's are equal, if
	be	equal		! so then branch to equal otherwise continue
	nop

	cmp	%l2, %l3	! If count of 1st uniq struct is less than 2nd,
	bl	negative	! branch to negaitive, otherwise continue
	nop

	mov	1, %i0		! Since counts are not equal, and 1st count is 
	ba	endif		! not less than 2nd one, then 1st count must
	nop			! be greater. Store 1 into %i0, so we can 
				! return this value from this function, and 
				! branch to endif always

equal:
	mov 	0, %i0		! Since counts of both uniq struct are equal,
	ba 	endif		! move 0 to %i0, so we can return this value 
	nop			! from this fucntion, and branch to endif 
				! always

negative:
	mov 	-1, %i0		! Since count of 1st uniq struct was less than
				! 2nd uniq struct, move -1 to %i0, so we can
				! return this value from this function, then
				! continue to endif below
endif:
	ret			! Return from subroutine
	restore			! Restore caller's window; in ret's delay slot
