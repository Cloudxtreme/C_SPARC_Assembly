/*
 * Filename: pa3Globals.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: Global variables for pa3.
 */


/*
 * C standard library headers 
 */
#include <stddef.h> // offsetof

/*
 * Assignment header(s)
 */
#include "pa3.h"

// Used in hashKeyMemberCompare() and anagramCompare()
size_t AnagramStructHashKeyOffset = offsetof(struct anagram, hashKey);
size_t AnagramStructWordOffset = offsetof(struct anagram, word);

// Used in hashString()
int HashPrime = HASH_PRIME;
int HashStartVal = HASH_START_VAL;

