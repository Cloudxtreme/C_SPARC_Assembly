#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main( int argc, char* argv[] ) {

    if (argc != 2) {
        fprintf(stderr, "Usage:\n\t%s num\n\n", argv[0]);
        fprintf(stderr, "\tnum - integer to calculate secret number for\n");
        exit(1);
    }

    char *endptr;

    errno = 0;
    long num = strtol(argv[1], &endptr, 10);
    if (errno) {
        fprintf(stderr, "Must enter a valid integer argument\n");
        exit(1);
    }

    long secret = nops(num);

    printf("The secret number for %ld is %ld\n", num, secret);

    return 0;
}

