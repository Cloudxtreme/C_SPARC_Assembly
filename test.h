/*
 * Filename: test.h
 * Author: Moiz Qureshi  
 * Userid: cs30xix
 * Description: Header for test.
 */

#ifndef TEST

#include <stdio.h>

#define TEST(EX)\
(void)((fprintf( stderr, "(%s:%d) %s: ", __FILE__, __LINE__, #EX)) && \
( (EX && fprintf(stderr, "\x1b[32mPASSED\x1b[0m\n")) ||\
(fprintf(stderr, "\x1b[31mFAILED\x1b[0m\n")) ))

#endif

