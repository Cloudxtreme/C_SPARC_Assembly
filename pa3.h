/*
 * Filename: pa3.h
 * Author: Moiz Qureshi  
 * Userid: cs30xix
 * Description: Header for pa3.
 */

#ifndef PA3_H
#define PA3_H

/*
 * C standard library headers 
 */
#include <stdio.h> // for FILE type

/*
 * Constants
 */
// arg parsing
#define ARG_STR_NON_EC "d:ho:s:"

#define DICT_FLAG    0x01
#define HELP_FLAG    0x02
#define DB_DEST_FLAG 0x04 
#define DB_SRC_FLAG  0x08
#define ERR_FLAG     0x10

#define CHAR_DICT_FLAG    'd'
#define CHAR_HELP_FLAG    'h'
#define CHAR_DB_DEST_FLAG 'o'
#define CHAR_DB_SRC_FLAG  's'

// hashing
#define HASH_START_VAL 7
#define HASH_PRIME     31

// file modes (use as the 2nd parameter to fopen)
#define FILE_READ_MODE  "r"    // open a file in read mode
#define FILE_WRITE_MODE "wb"   // open a file in binary write mode

/* 
 * Enum Definitions 
 */
// usage printing
enum usageMode { USAGE_SHORT, USAGE_LONG };

// program mode to execute
enum programMode { MODE_USAGE, MODE_SETUP_DB, MODE_FIND_ANAGRAMS };

// error codes; suffix "_M" indicates code uses the errorMsg
enum errorCode { 
  ERR_NONE,                     // no error present 
  ERR_ERRNO_M,                  // system call failed, check errno for info
  ERR_DB_WRITE_M,               // failed database write 
  ERR_INV_FLAG_OR_ARG,          // invalid command line flag or missing arg
  ERR_MUTUAL_EXCL,              // use mutual exclusive flags 
  ERR_DB_PARSE,                 // could not build array from database file
  ERR_DB_DEST_FLAG_DEPENDENCE,  // DB_DEST flag without DICT flag
  ERR_EXTRA_ARGS_M,             // extra args on command-line
  ERR_USER_INTERFACE,           // error encountered during user interface
  ERR_CREATE_ANAGRAM            // error creating anagram in setupDB 
};

/* 
 * Struct Definitions 
 */
// Information about command line argument parsing
struct argInfo {
  int flags;
  enum programMode programMode;
  const char *dictFilename;
  const char *anagramDB;
};

// Information about printing error message
#define ERROR_MSG_SIZE 1024
struct errorInfo {
  enum errorCode errorCode;
  char errorMsg[ERROR_MSG_SIZE];
};

// Create one anagram struct per word in dictionary file
struct anagram {
  char *word;   // Original word from dictionary
  int hashKey;  // hashed value of lower-case sorted word
};

/*
 * The anagramInfo struct holds info about the sorted array of struct anagram
 * generated from the database file
 */
struct anagramInfo {
  struct anagram *anagramPtr; // Ptr to array of sorted struct anagram
  size_t numOfAnagrams;       // number of anagrams in anagramPtr
};

/* 
 * C Function Prototypes 
 * */
int createAnagram(const char *src, struct anagram *anagram);
void findAnagrams(const struct argInfo *argInfo, struct errorInfo *errorInfo);
void lowerCaseSortString(const char *src, size_t n, char *dest);
void printErrors(const struct errorInfo *errorInfo, const char *progName);
void parseArgs(int argc, char * const argv[], struct argInfo *argInfo,  
    struct errorInfo *errorInfo);
int parseDB(FILE *stream, struct anagramInfo *anagramInfo);
int readAnagramFromDB(FILE *stream, struct anagram *anagram);
void setErrorInfo(struct errorInfo *errorInfo, enum errorCode e, 
    const char *errorMsg);
void setupDB(const struct argInfo *argInfo, struct errorInfo *errorInfo);
void usage(FILE *stream, enum usageMode u, const char *progName);
int userInterface(const struct anagramInfo *angramInfo);
int writeAnagramToDB(const struct anagram *anagram, FILE *stream);

/* 
 * Assembly Function Prototypes 
 */
int anagramCompare(const void *p1, const void *p2);
int charCompare(const void *p1, const void *p2);
int hashKeyMemberCompare(const void *p1, const void *p2);
int hashString(const char *str);

#endif /* PA3_H */

