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
 */




