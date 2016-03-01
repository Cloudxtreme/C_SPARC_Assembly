/*
 * Filename: setErrorInfo.c
 * Author: TODO: Enter your name
 * Userid: TODO: Enter your cs30x login id
 * Description: Sets members of sturct errorInfo.
 */

#include <string.h> // strncpy, memset

#include "pa4.h" // ERROR_MSG_SIZE, struct errorInfo

/*
 * TODO Function headers are always needed!
 */
void setErrorInfo(struct errorInfo *errorInfo, enum errorCode e,
    const char *errorMsg) {

  /* Set error code */
  errorInfo->errorCode = e;

  /* Set message if not null */
  if(errorMsg) {
    (void) strncpy(errorInfo->errorMsg, errorMsg, ERROR_MSG_SIZE);  
    errorInfo->errorMsg[ERROR_MSG_SIZE-1] = '\0'; 
  }
  else {
    (void) memset(errorInfo->errorMsg, 0, ERROR_MSG_SIZE);
  }
}
