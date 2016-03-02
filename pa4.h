/*
 * Filename: pa4.h
 * Author: Moiz Qureshi
 * Userid: cs30xix
 * Description: Header file for pa4 assignment
 */

#ifndef _PA4_H
#define _PA4_H

/* Needed for FILE definition in prototypes below. */
#include <stdio.h>
#include <time.h>

/*
 * Options bitmasks
 */
#define OPT_COUNT       0x01
#define OPT_IGNORE_CASE 0x02
#define OPT_SORT_OUTPUT 0x04
#define OPT_SORT_INPUT  0x08
#define OPT_HELP        0x10
#define OPT_SUMMARY     0x20

/*
 * Command line flags (most correspond to options, but some set outputMode)
 */
#define FLAG_DUP_ONLY     'd'
#define FLAG_DUP_ALL      'D'
#define FLAG_HELP         'h'
#define FLAG_IGNORE_CASE  'i'
#define FLAG_SORT_OUTPUT  's'
#define FLAG_SORT_INPUT   'S'
#define FLAG_COUNT        'c'
#define FLAG_SUMMARY      'x'
#define FLAG_UNIQUE       'u'

/*
 * Arg string for getopt
 */
#define ARG_STRING_NON_EC "cdDhisSux"

/*
 * File open modes.
 */
#define FILE_READ_MODE "rb"
#define FILE_WRITE_MODE "wb"

/*
 * Enums
 */
/* Which version of the usage to print */
enum usageMode { 
  UsageShort,
  UsageLong 
};

/* What error was encountered */
enum errorCode { 
  ErrNone,
  ErrMutualExcl,
  ErrInvFlag,
  ErrErrno_M,
  ErrExtraArgs_M
};

/* How to print output */
enum outputMode {
  DuplicateAll,		/* -D flag: like -d but print all duplicate lines. */
  DuplicateOnly,	/* -d flag: only print duplicate lines.        */
  Unique,		      /* -u flag: only print unique lines.           */
  Regular		      /* default mode: print 1st copy of each line   */
};

/*
 * Structs
 */
/* Stores information parsed from command line */
struct argInfo {
  unsigned int options;
  enum outputMode outputMode;
  char *inFile;
  char *outFile;
};

/* Used to pass error code and message */
#define ERROR_MSG_SIZE 1024
struct errorInfo {
  enum errorCode errorCode;
  char errorMsg[ERROR_MSG_SIZE];
};

/* Used to keep track of each group of successive, duplicate lines */
struct uniq {
  unsigned int count;
  char *line;
  char *dups;		/* To hold duplicate lines for -D option */
};

/* Typedef this data structure so we can easily modify implementation later. */
typedef struct uniq uniq_t;

/* Stores information about array of uniq_t for whole file */
struct uniqInfo {
  uniq_t *uniqPtr;
  unsigned int numOfEntries;
};

/* Stores information about array of pointers to lines of input file */
struct parsedInputInfo {
  char **parsedInputPtr;
  unsigned int numOfEntries;
};

/* Function Prototypes */
int compareCount(const void *p1, const void *p2);

int compareLine(const void *p1, const void *p2);

int findUniq(
    const struct parsedInputInfo *parsedInputInfoPtr, 
    const struct argInfo *argInfoPtr, 
    struct uniqInfo *uniqInfoPtr,
    struct errorInfo *errorInfoPtr
    );

int pa4gettimeofday( struct timeval *tp, struct timezone *tzp );

void parseArgs(
    int argc, 
    char * const argv[], 
    struct argInfo *argInfo,  
    struct errorInfo *errorInfo
    );

int parseInputStream(
    FILE *stream, 
    const struct argInfo *argInfoPtr, 
    struct parsedInputInfo *parsedInputInfoPtr, 
    struct errorInfo *errorInfoPtr
    );

void printErrors(const struct errorInfo *errorInfoPtr, const char *progName);

void printResults(
    FILE *outFile,
    const struct argInfo *argInfoPtr,
    const struct uniqInfo *uniqInfoPtr
    );

void runUniq(const struct argInfo *argInfoPtr, struct errorInfo *errorInfoPtr);

int sortInputCompare (const void *p1, const void *p2);

void setErrorInfo(
    struct errorInfo *errorInfoPtr, 
    enum errorCode e, 
    const char *errorMsg
    );

int strIgnoreCaseCmp(const char *s1, const char *s2, unsigned int n);

void usage(FILE *stream, enum usageMode u, const char *progName);

#endif /* _PA4_H */
