/* Filename: pa1.h
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Function prototypes and defines for PA1
 * Date: 1/19/2016
 * Sources of Help: PA1 Handout
 */

#ifndef _MAIN_H
#define _MAIN_H

#define NUM_ARGV 4
#define BASE 10
#define MIN_XOR_CHAR 33
#define OFFSET_XOR_CHAR 93
#define MIN_WIDTH 3
#define OFFSET_WIDTH 36
#define MIN_SPEED 100000
#define OFFSET_SPEED 900000

#include <stdio.h>
#include <stdlib.h>

void line (char xorChar, long charpos, long width);

void drawXOR (char xorChar , long width, long speed);

long checkRange(long minRange, long offset, long value);

void printChar( char ch );

long isOdd(long num);

long isNegative(long num);

#endif /*_MAIN_H*/
