// memory2.c
//
// Every malloc needs exactly one matching free. Memory you allocate and
// never free is *leaked*: in a long-running program, leaks pile up until
// you run out of memory.
//
// LeakSanitizer (part of AddressSanitizer) checks for leaks when the program
// exits. All the checks pass, yet the program fails. Read the leak report
// and fix the leaks.

// I AM NOT DONE

#include <stdlib.h>
#include <string.h>

#include "clings.h"

char *repeat(const char *s, int times) {
    size_t len = strlen(s);
    char *out = malloc(len * times + 1);
    if (out == NULL) {
        return NULL;
    }
    out[0] = '\0';
    for (int i = 0; i < times; i++) {
        strcat(out, s);
    }
    return out;
}

int main(void) {
    char *a = repeat("ab", 3);
    CHECK_STR(a, "ababab");

    char *b = repeat("-", 5);
    CHECK_STR(b, "-----");

    for (int i = 0; i < 3; i++) {
        char *tmp = repeat("x", i);
        CHECK_INT(strlen(tmp), i);
    }

    return clings_report();
}
