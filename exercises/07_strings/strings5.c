// strings5.c
//
// Building strings safely: `snprintf` works like printf, but writes into a
// buffer instead of the screen, and never writes more than the size you give
// it (it always adds the '\0', truncating if necessary):
//
//     char buf[32];
//     snprintf(buf, sizeof(buf), "%s is %d years old", name, age);
//
// Common format specifiers:
//     %d  int        %ld  long        %zu  size_t
//     %f  double     %.2f double with 2 decimals
//     %s  string     %c   char        %x  hex        %%  a literal %
//
// Avoid `sprintf` and `strcpy` into fixed buffers: they don't know the size
// and happily overflow.
//
// Make each format string produce the expected output.

// I AM NOT DONE

#include <stdio.h>

#include "clings.h"

int main(void) {
    char buf[64];

    snprintf(buf, sizeof(buf), "FIXME", "Ada", 36);
    CHECK_STR(buf, "Ada is 36 years old");

    snprintf(buf, sizeof(buf), "FIXME", 3.14159);
    CHECK_STR(buf, "pi is about 3.14");

    snprintf(buf, sizeof(buf), "FIXME", 255);
    CHECK_STR(buf, "255 in hex is ff");

    snprintf(buf, sizeof(buf), "FIXME", 99);
    CHECK_STR(buf, "battery: 99%");

    // snprintf returns the length the full string WOULD have had.
    // GCC is clever enough to spot this truncation at compile time and warn
    // about it. Here we're truncating on purpose, so we switch that one
    // warning off for these lines.
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-truncation"
#endif
    char tiny[6];
    int needed = snprintf(tiny, sizeof(tiny), "%s", "truncated");
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
    CHECK_STR(tiny, FIXME);
    CHECK_INT(needed, FIXME);

    return clings_report();
}
