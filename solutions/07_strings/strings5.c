// strings5.c - solution

#include <stdio.h>

#include "clings.h"

int main(void) {
    char buf[64];

    snprintf(buf, sizeof(buf), "%s is %d years old", "Ada", 36);
    CHECK_STR(buf, "Ada is 36 years old");

    snprintf(buf, sizeof(buf), "pi is about %.2f", 3.14159);
    CHECK_STR(buf, "pi is about 3.14");

    snprintf(buf, sizeof(buf), "%d in hex is %x", 255, 255);
    CHECK_STR(buf, "255 in hex is ff");

    snprintf(buf, sizeof(buf), "battery: %d%%", 99);
    CHECK_STR(buf, "battery: 99%");

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
    CHECK_STR(tiny, "trunc");
    CHECK_INT(needed, 9);

    return clings_report();
}
