/*
 * Filename: pa4Strings.h
 * author: TODO
 * userid: TODO
 * Description: Strings used in pa4 assignment
 */
#ifndef _PA4_STRINGS_H
#define _PA4_STRINGS_H

/*
 * Strings for long options
 */
#define STR_LONG_OPT_DUP_ONLY     "repeated"
#define STR_LONG_OPT_DUP_ALL      "all-repeated"
#define STR_LONG_OPT_HELP         "help"
#define STR_LONG_OPT_IGNORE_CASE  "ignore-case"
#define STR_LONG_OPT_SORT_OUTPUT  "sort-output"
#define STR_LONG_OPT_SORT_INPUT   "sort-input"
#define STR_LONG_OPT_COUNT        "count"
#define STR_LONG_OPT_SUMMARY      "summary"
#define STR_LONG_OPT_UNIQUE       "unique"

/*
 * Usage strings
 */
#define STR_USAGE_SHORT "Try '%s --help' for more information.\n"

#define STR_USAGE_LONG "Usage: %s [-d|-D|-u] [-cisSx] [inputfile [outputfile]]"\
    "\nDiscard all but one of successive identical lines from inputfile "\
    "(or stdin),\nwriting to outputfile (or stdout).\n"\
    "\n"\
    "Mutually exclusive options (only one of):\n"\
    " -d, --repeated\t\tonly print duplicate lines\n"\
    " -D, --all-repeated\tlike -d but print all duplicate lines\n"\
    "\t\t\t\t-c option ignored if combined with this option\n"\
    " -u, --unique\t\tonly print unique lines\n"\
    "\n"\
    "Non-mutually exclusive options (any combination of):\n"\
    " -c, --count\t\tprefix lines by the number of occurrences\n"\
    " -i, --ignore-case\tignore differences in case when comparing\n"\
    " -s, --sort-output\tsort output\n"\
    "\t\t\t\tif -c option specified, sort by count (descending order)\n"\
    "\t\t\t\telse sort by lines\n"\
    " -S, --sort-input\tact as if the input was sorted first before being "\
    "processed\n"\
    " -x, --summary\t\tprint executive summary of results\n"\
    "\n"\
    " -h, --help\t\tdisplay this help and exit\n"

/*
 * String for printing results 
 */
#define STR_PRINT_LINE "%s"
#define STR_PRINT_COUNT "%4d "
#define STR_PRINT_SUMMARY "\n=== Results ===\n"\
    "Entries:\n"\
    "\tDuplicates: %d\n"\
    "\tUnique:     %d\n"\
    "\tTotal:      %d\n"\
    "Lines:\n"\
    "\tDuplicates: %d\n"\
    "\tUnique:     %d\n"\
    "\tTotal:      %d\n"\
    "\nGenerated at: %s\n"

#define STR_TIME_FORMATER "%T"

/*
 * Error Strings
 */
#define STR_ERR_MUTUAL_EXCL "Mutually exclusive options were given!\n"
#define STR_ERR_FIND_UNIQ "Finding unique lines"
#define STR_ERR_PARSE_INPUT "Parsing input"
#define STR_ERR_EXTRA_ARGS "Extra operand '%s'.\n" 

#endif /* PA4_STRINGS_H */
