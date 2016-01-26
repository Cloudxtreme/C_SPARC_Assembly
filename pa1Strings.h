/*
 * Filename: pa1Strings.h
 * Author: CSE30 Tutors - Given file
 * Userid: cs30xix
 * Description: String defines for PA1
 * Date: 1/24/16
 * Sources of Help: This is a given, copied over file from public
 */

#ifndef PA1_STRINGS_H
#define PA1_STRINGS_H
#define USAGE "\nUsage: ./pa1 xorChar width speed\n\
  xorChar (must be an ASCII value within the range of [33 - 126])\n\
  width   (must be an numerical value within the range [3 - 39])\n\
          (must be an odd value)\n\
  speed   (must be an numerical value within the range [100000 - 1000000])\n\n"

#define INT_ERR "\n    \"%s\" is not an integer\n\n"


#define XOR_ERR "\n    xorChar(%lu) (must be an ASCII value within the range\
  [%d - %d])\n\n"
#define WIDTH_ERR "\n    width(%lu) (must be within the range [%u - %u])\n\n"
#define WIDTH_ODD_ERR "\n    width(%lu) (must be an odd integer)\n\n"
#define SPEED_ERR "\n    speed(%lu) (must be within the range [%u - %u])\n\n"

#endif /* PA1_STRINGS_H */
