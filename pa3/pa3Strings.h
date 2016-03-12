/*
 * Filename: pa3Strings.h
 * Author: Moiz Qureshi 
 * Userid: cs30xix
 * Description: Strings for pa3.
 */

#ifndef PA3_STRING_H
#define PA3_STRING_H

/* Standard string */
#define STR_DEF_ANAGRAM_DB "anagram_database.db"
#define STR_DB_BUILT "Anagram database file \"%s\" built.\n"
#define STR_USER_PROMPT "\nEnter a word to search for anagrams [^D to exit]: "
#define STR_NO_ANAGRAMS "No anagrams found."
#define STR_FOUND_ANAGRAMS "Anagram(s) are:"
#define STR_ANAGRAM "%s "

#define STR_USAGE_SHORT "Try '%s -h' for more information.\n"
#define STR_USAGE_LONG "usage: %s [-d dict_name [-o db_dest]] | [-s db_src] "\
  "| [-h]\n"\
  "Interactive anagram search.\n"\
  "\nStartup:\n"\
  "\t-h\t\t print long usage.\n"\
  "\nSetup Database:\n"\
  "\t-d <dict_name>\t source dictionary for database creation.\n"\
  "\t-o <db_dest>\t custom database file name.\n"\
  "\nFind Anagrams:\n"\
  "\t-s <db_src>\t path to custom source database file.\n"

/* Error strings */
#define STR_ERR_DB_WRITE "Error writing word \"%s\" to database.\n"
#define STR_ERR_MUTUAL_EXCL "Setup flags (-d, -o) and find anagrams flags "\
  "(-s) are mutually exclusive.\n"
#define STR_ERR_DB_PARSE "Could not parse database file. Memory limit likely "\
  "exceeded.\n"
#define STR_ERR_DB_DEST_FLAG_DEPENDENCE "Database destination flag (-o) "\
  "requires the presence of the dictionary source flag (-d).\n"
#define STR_ERR_EXTRA_ARGS "Extra operand '%s'.\n" 
#define STR_ERR_USER_INTERFACE "Early termination of user prompt due to "\
  "error.\n"
#define STR_ERR_CREATE_ANAGRAM "Could not build struct anagram. Memory limit "\
  "likely reached.\n"

#endif /* PA3_STRING_H */
