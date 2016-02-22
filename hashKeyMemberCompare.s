/*
 * Filename: hashKeyMemberCompare.s  
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Compare the hash keys in two strcut anagrams, this function
 * 		used in bsearch() in userInterface()
 * Date: 2/22/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.2
 */

	.global hashKeyMemberCompare 	! Decalre the symbol to be globally
					! visible, so we can call this function
					! from other modules

	.section ".text"	! The text segment begins here

/*
 * Function name: hashKeyMemberCompare() 
 *
 * Function prototype: 
 * 	int hashKeyMemberCompare( const void *p1, const void *p2 );
 *
 * Description: Compare the hash keys in two structu anagrams that are passed 
 * 		in. Access the hashKey members by using the approrpiate 
 * 		offsets.
 *             
 * Parameters: 
 *      arg 1 - const void *p1 -- pointer to first struct anagram
 *      arg 2 - const void *p2 -- pointer to second struct anagram
 *
 * Side Effects: Compares the hash keys of two struct anagrams, and determines
 * 		 which is greater/lesser or if they are equal
 * 
 * Error Conditions: None
 *
 * Return Values: 
 * 	-1 - if the first anagram's hash key is smaller
 * 	 1 - if the first anagram's hash key is larger
 * 	 0 - if the hash keys of both anagrams are the same
 *
 * Registers Used: 
 * 	%i0 - pointer to first anagram struct
 *	%i1 - pointer to second anagram struct
 *
 * 	%l0 - holds value for hashKey member offset
 * 	%l1 - holds value of first anagram hashKey
 * 	%l2 - holds value of second anagram hashKey
 */

hashKeyMemberCompare:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was 
				! calculated.

	clr 	%l0

	/* Grab the value of hashKey member offset from
	 * pa3Globals.c, store in %l0.
	 */
	set	AnagramStructHashKeyOffset, %l0
	ld	[%l0], %l0

	


