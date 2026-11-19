// errors1.c - solution

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "clings.h"

bool parse_int(const char *str, int *out) {
    char *end;
    errno = 0;
    long v = strtol(str, &end, 10);
    if (end == str || *end != '\0' || errno == ERANGE) {
        return false;
    }
    if (v < INT_MIN || v > INT_MAX) {
        return false;
    }
    *out = (int)v;
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
    CHECK(!parse_int("3000000000", &v));
    CHECK_INT(v, 999);

    return clings_report();
}
