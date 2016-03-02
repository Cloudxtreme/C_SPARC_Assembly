/*
 * Filename: strIgnoreCaseCmp.s 
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Compares two strings character by character up to n characters
 * 		ignoreing case.
 * Date: 3/2/16 
 * Sources of Help: PA4 Assignment Sheet, PA4 Discussion Slides pt.1
 */

	.global strIgnoreCaseCompare 	! Declare the symbol to be globally
					! visible, so we can call this function
					! from other modules

	.section ".text"		! The text segment begins here

/*
 * Function name: strIgnoreCaseComp()
 *	
 * Function prototype: 
 *  	int strIgnoreCaseComp( const char *s1, const char *s2 unsigned int n) ;
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
 */

strIgnoreCaseCompare:
	save	-96, %sp, -96	! Save the caller's window; if differen than 
				! -96, then comment on how that value was 
				! calculated.

	



