#ifndef PA2_H
#define PA2_H


/* # of command line arguments, including the name of the program */
#define MIN_ARGS 2
#define MAX_ARGS 4

/*
 * NOTE: The min values are INCLUSIVE, the max values are EXCLUSIVE.  You need
 * to account for this when printing out the usage and error strings.  Make
 * sure your output matches the sample output provided.
 */
#define MIN_HR 0
#define MAX_HR 24
#define HR_OFFSET 23

#define MIN_MINUTE 0
#define MAX_MINUTE 60
#define MINUTE_OFFSET 59

#define MIN_SEC 0
#define MAX_SEC 60
#define SEC_OFFSET 59

/* Indices of clock array */
#define HR_INDEX 0
#define MIN_INDEX 1
#define SEC_INDEX 2

#define BASE 10

#define MIN_INTERVAL 1
#define MAX_INTERVAL 86399
#define INTERVAL_OFFSET 86398
#define DEF_INTERVAL 1

#define MIN_TICKS 0
#define MAX_TICKS 61
#define DEF_TICKS 7

#define REQ_SEPARATORS 2

#define TIME_STR_DELIMITER ':'

/* Create any bit masks you need in here */

/* Create constants for the binary characters that get printed */

/*
 * parseStartTime() errors:
 * Check for the following errors IN THIS ORDER!
 */
#define ERR_TIME_FORMAT  0x1 /* Invalid start time string */
#define ERR_HR_VALUE     0x2 /* Hour value invalid */
#define ERR_HR_RANGE     0x4 /* Hour value out of range */
#define ERR_MIN_VALUE    0x8 /* Min value invalid */
#define ERR_MIN_RANGE   0x10 /* Min value out of range */
#define ERR_SEC_VALUE   0x20 /* Sec value invalid */
#define ERR_SEC_RANGE   0x40 /* Sec value out of range */

/* C routines */
void updateClockDecimal( long clockDecimal[], long intervalSeconds );
void usage( const char * programName );
void displayBCDClock( const unsigned char clockBCD[] );
unsigned long parseStartTime( long clockDecimal[], const char * time );


/* Assembly routines */
void printChar( char ch );
long isNegative( long num );
long checkRange( long minRange, long offset, long value );
long updateClockDecimalValue( long * clockVal, long updateAmt, long maxVal );
void convertToBCD( const long clockDecimal[], unsigned char clockBCD[] );

#endif /* PA2_H */

