 /*
 * Filename: testreadAnagramFromDB.c
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: Tester for readAnagramFromDB()
 */

#include <stdio.h>

#include "pa3.h"
#include "test.h"


#define DB_FILE "ref/small_dict1_database.db"
#define READ_MODE "r"

/*
 * TODO Function headers are always needed!
 */
static void testreadAnagramFromDB() {
             
  FILE *db = fopen(DB_FILE, READ_MODE);
  struct anagram test;

  int err = readAnagramFromDB(db, &test);

  printf("%d", err);


  fclose(db);

}

/*
 * TODO Function headers are always needed!
 */
int main( void ) {
  (void) fprintf( stderr, "Starting testreadAnagramFromDB\n" );

  testreadAnagramFromDB();

  (void) fprintf( stderr, "Done.\n" );

  return 0;
}



