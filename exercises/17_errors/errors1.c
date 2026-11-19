// errors1.c
//
// C has no exceptions. Functions report errors through return values, and
// the conventional pattern is:
//
//   * return a success/failure indicator (bool, or an int error code), and
//   * deliver the actual result through an output pointer.
//
// `atoi("hello")` returns 0, the same as atoi("0"), so you can't tell if it
// failed. `strtol` is the robust alternative:
//
//     char *end;
//     errno = 0;
//     long v = strtol(str, &end, 10);
//     // end == str          -> no digits at all
//     // *end != '\0'        -> trailing junk after the number
//     // errno == ERANGE     -> number too big for a long
//
// Implement `parse_int`. It must reject anything that isn't entirely a valid
// int (in the range INT_MIN..INT_MAX), and leave *out alone on failure.

// I AM NOT DONE

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "clings.h"

bool parse_int(const char *str, int *out) {
    *out = atoi(str);
    return true;
}

int main(void) {
    int v = -1;

    CHECK(parse_int("42", &v));
    CHECK_INT(v, 42);
    CHECK(parse_int("-17", &v));
    CHECK_INT(v, -17);

    v = 999;
    CHECK(!parse_int("", &v));
    CHECK(!parse_int("hello", &v));
    CHECK(!parse_int("12abc", &v));
    CHECK(!parse_int("99999999999999999999", &v));
    CHECK(!parse_int("3000000000", &v));  // fits in a long, not in an int
    CHECK_INT(v, 999);                   // unchanged by failed parses

    return clings_report();
}
