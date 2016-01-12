/*
 * Filename: pa0.h
 * Author: : Moiz Qureshi
 * Userid: cs30xix
 * Description: Function prototypes and defines for PA0
 * Date: Jan. 10, 2016
 * Sources of Help: PA0 Assignment Sheet, PA0 Code Handout
 */

 #ifndef PA0_H
 #define PA0_H

 #define EXPECTED_ARGS 1

 /* User defined types used in PA0 */

 struct DueDate {
  const char *month;
  unsigned int day;
  unsigned int year;
 };

 /* Function prototypes for the C and assembly routines used in PA0 */

void printDueDate( const struct DueDate *dueDate );
void printWelcome( const char *string );

int squareNum( int num );

#endif /* PA0_H */

