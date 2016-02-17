/*
 * Filename: hashString.s 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Creates an integer hash code from string argument passed in.
 * Date: 2/16/16 
 * Sources of Help: PA3 Assignment Sheet, PA3 Discussion Slides pt.1
 */

	.global	hashString	! Declare the symbol to be globally visible so
				! we can call this function from other modules

	.section ".text"	! The text segment begins here



/*
 * Function name: hashString()
 *
 * Function prototype: int hashString( const char *str );
 *
 * Description: Creates an integer hash code from str by using Java's
 * 		String.hashCode() formula:
 *             
 *	int hashString(const char *str) {
 *	  int hash = HASH_START_VAL;
 *	  int strLen = strlen(str);
 *
 *	  int i;
 *	  for(i = 0; i < strLen; i++) 
 *	    hash = hash * HASH_PRIME + str[i];
 *            
 *        return hash
 *	}
 *          
 * Parameters: 
 *      arg 1 - const char *str - string to find hash for
 *
 * Side Effects: None
 *
 * Error Conditions: None
 *
 * Return Values: integer hash calculated using Java's String.hashCode() 
 * 		  forumla, on string str
 *
 * Registers Used: 
 * 	
 * 	%i0 -- const char *str
 * 
 * 	%l0 -- int HashStartVal
 * 	%l1 -- int HashPrime
 * 	%l2 -- int hash
 * 	%l3 -- int strLen
 * 	%l4 -- int i (for-loop counter)
 * 	%l5 -- char *str
 * 	%l6 -- char str[i] 
 */

hashString:
	save	%sp, -96, %sp	! Save the caller's window; if different than
				! -96, then comment on how that value was 
				! calculated.

	clr	%l0		! Clear %l0 register
	clr 	%l1		! Clear %l1 register
	clr 	%l2		! Clear %l2 register
	clr	%l3		! Clear %l3 register
	clr 	%l4		! Clear %l4 register
	clr 	%l5		! Clear %l5 register
	clr	%l6		! Clear %l6 register
	
	set	HashStartVal, %l0	! Copy value of HashStartVal into %l0 
	ld	[%l0], %l0

	set	HashPrime, %l1		! Copy value of HashPrime into %l1
	ld 	[%l1], %l1		

	mov	%i0, %l5	! Copy value of *str into %l5
	mov	%l0, %l2	! Intialize value of hash to HashStartVal

	mov	%l5, %o0	! Copy *str into %o0, so we can call strlen().
	call	strlen
	nop

	mov	%o0, %l3	! Copy result of strlen(), into %l3

	cmp	%l4, %l3	! If i is greater than or equal to strLen, then
	bge	endloop		! branch to endloop, otherwise continue to 
	nop			! loop branch

loop:
	mov 	%l2, %o0	! Find product of hash*HashPrime  
	mov	%l1, %o1	
	call	.mul
	nop

	mov	%o0, %l2 	! Store result of hash*HashPrime back into %l2
	ldub	[%l5], %l6	! Get value of str[i]
	add     %l2, %l6, %l2   ! Add str[i] to hash*HashPrime	
	
	inc 	%l5		! Increment *str by 1 
	inc 	%l4		! Increment i by 1


	cmp 	%l4, %l3	! If i < strLen, then continue looping, 
	bl	loop		! otherwise continue below to endloop
	nop

endloop:
	mov 	%l2, %i0	! Copy hash value into %i0, so we can return 
				! this value from this function

	ret			! Return from subroutine	
	restore			! Restore caller's window; in ret's delay slot










