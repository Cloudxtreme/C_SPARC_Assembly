/*
 * Filename: pa4Globals.c
 * Author: Moiz Qureshi
 * UserId: cs30xix
 * Description: Global variables for assembly files.
 */
#include <stdio.h> // stdout
#include <stdlib.h>
#include <stddef.h> //offsetof

#include "pa4.h"

/*
 * Needed for pa4.s
 */
int FlagHelp = OPT_HELP;
int ErrorCodeErrNone = ErrNone;

int UsageModeUsageLong = UsageLong;
FILE *StandardOut = stdout;

int ErrorInfoErrorCodeOffset = offsetof(struct errorInfo, errorCode);
int ArgInfoOptionsOffset = offsetof(struct argInfo, options);

int errorSuccess = EXIT_SUCCESS;
int errorFailure = EXIT_FAILURE;

/*
 * Needed for compareCount.s
 */
int UniqCountOffset = offsetof(uniq_t, count);

/*
 * Needed for compareLine.s
 */
int UniqLineOffset = offsetof(uniq_t, line);

