/*
 * Filename: anagramCompare.s  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Compare the hash keys and words in two strcut anagrams, 
 * 		this function; used in parseDB()
 * Date: 2/22/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.2
 */

	.global anagramCompare 	! Decalre the symbol to be globally
				! visible, so we can call this function
				! from other modules

	.section ".text"	! The text segment begins here

/*
 * Function name: anagramCompare() 
 *
 * Function prototype: 
 * 	int anagramCompare( const void *p1, const void *p2 );
 *
 * Description: Compare the hash keys and words in two structu anagrams that 
 * 		are passed in. Access the hashKey and word members by using 
 * 		the approrpiate offsets.
 *             
 * Parameters: 
 *      arg 1 - const void *p1 -- pointer to first struct anagram
 *      arg 2 - const void *p2 -- pointer to second struct anagram
 *
 * Side Effects: Compares the hash keys and words of two struct anagrams, 
 * 		 and determines which is greater/lesser or if they are equal
 * 
 * Error Conditions: None
 *
 * Return Values: 
 * 	-1 - if the first anagram is smaller
 * 	 1 - if the first anagram is larger
 * 	 0 - if the hash keys of both anagrams are the same
 *
 * Registers Used: 
 * 	%i0 - pointer to first anagram struct
 *	%i1 - pointer to second anagram struct
 *
 * 	%l0 - holds value for hashKey member offset
 * 	%l1 - holds value for word member offset
 * 	%l2 - holds value of first anagram hashKey
 * 	%l3 - holds value of second anagram hashKey
 * 	%l4 - holds pointer to first anagram word
 * 	%l5 - holds pointer to second anagram word
 */

anagramCompare:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was 
				! calculated.

	/* Clear the local registers */
	clr 	%l0
	clr 	%l1
	clr 	%l2
	clr 	%l3
	clr 	%l4
	clr	%l5

	/* Grab the value of hashKey and word member offset from
	 * pa3Globals.c, store in %l0 and %l1 respectively.
	 */
	set	AnagramStructHashKeyOffset, %l0
	ld	[%l0], %l0
	
	set	AnagramStructWordOffset, %l1
	ld	[%l1], %l1

	add	%l0, %i0, %l2 	! Add offset to first anagram pointer, to get
	ld	[%l2], %l2	! address of hashKey member, then load its 
				! value into register %l1

	add	%l0, %i1, %l3	! Add offset to second anagram pointer, to get
	ld 	[%l3], %l3	! address of hashKey member, then load its 
				! value into register %l2

	cmp	%l2, %l3	! If first hashKey is less than second, then
	bl	lessThan	! branch to lessThan
	nop

	cmp	%l2, %l3	! If both hashKeys are equal then branch to
	be	equal		! equal
	nop

greaterThan:
	mov	1, %i0		! Since first hashKey is not less than second,
	ba	endif		! and not equal to second, then move 1 to 
	nop			! to %i0, so we can return 1 from this 
				! function. Then branch to endif always.

lessThan:
	mov	-1, %i0		! Since first hashKey is less than second, 
	ba	endif		! move -1 to %i0, so we can return -1 from
	nop			! this function. Then branch to endif always.

equal:
	add	%l1, %i0, %l4 	! Add word offset to 1st anagram pointer, to 
	ld	[%l4], %o0	! get address of word member, then load its 
				! value into %o0

	add	%l1, %i1, %l5	! Add word offset to 2nd anagram pointer, to 
	ld	[%l5], %o1	! get address of word member, then load its
				! value into %o1

	call 	strcmp		! Call strcmp on first and second word
	nop

	cmp	%o0, %g0	! Compare return from strcmp(), if less
	bl	lessThan	! than 0, then branch to lessThan
	nop	

	cmp	%o0, %g0	! Compare return from strcmp(), if greater
	bg	greaterThan	! than 0, then brach to greaterThan
	nop

	mov	0, %i0		! Store return value from strcmp() into 
				! %i0, so we can return that value from
				! this function. Then continue to endif
				! below.

endif:
	ret			! Return from subroutine
	restore			! Restore caller's window; in ret's delay slot





