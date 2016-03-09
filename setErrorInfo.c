/*
 * Filename: setErrorInfo.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: Sets members of sturct errorInfo.
 */

#include <string.h> // strncpy, memset

#include "pa4.h" // ERROR_MSG_SIZE, struct errorInfo

/*
 * Function Name: setErrorInfo()
 *
 * Function Prototype:
 *  setErrorInfo( struct errorInfo *errorInfo, enum errorCode e, 
 *                const char *errorMsg );
 *
 * Function Description: Sets the errorCode passed in into struct errorInfo
 *                       *errorInfo, and also the errorMsg
 *
 * Parameters: 
 *    arg 1 - struct errorInfo *errorInfo
 *    arg 2 - enum errorCode e
 *    arg 3 - const char *errorMsg
 *
 * Side Effects: Set the errorCode and errorMsg members of struct errorInfo
 *
 * Error Conditions: None
 *
 * Return Value: None
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
