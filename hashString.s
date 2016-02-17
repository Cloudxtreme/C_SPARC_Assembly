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
	
	set	HashStartVal, %l0	! Copy value of HashStartVal itno %l0 
	set 	HashPrime, %l1		! Copy value of HashPrime into %l1

	mov	%l0, %l2	! Intialize value of hash to HashStartVal

	mov	%i0, %o0	! Copy *str into %o0, so we can call strlen().
	call	strlen
	nop

	mov	%o0, %l2	! Copy result of strlen(), into %l2

	cmp	%l4, %l3	! If 
	bge	endloop
	nop

loop:
	



endloop:
