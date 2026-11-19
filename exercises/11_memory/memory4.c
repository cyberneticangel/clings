// memory4.c
//
// Strings on the heap. A function that returns a *new* string must malloc
// room for it, and the caller becomes responsible for freeing it.
//
// Remember: a string of length n needs n + 1 bytes!
//
// Fix `my_strdup` and implement `concat`.

// I AM NOT DONE

#include <stdlib.h>
#include <string.h>

#include "clings.h"

// Returns a heap-allocated copy of s.
char *my_strdup(const char *s) {
    char *copy = malloc(strlen(s));
    if (copy != NULL) {
        strcpy(copy, s);
    }
    return copy;
}

// Returns a new heap-allocated string containing a followed by b.
char *concat(const char *a, const char *b) {
    // TODO
}

int main(void) {
    char *s = my_strdup("duplicate me");
    CHECK_STR(s, "duplicate me");
    free(s);

    char *both = concat("foo", "bar");
    CHECK_STR(both, "foobar");
    free(both);

    char *empty = concat("", "");
    CHECK_STR(empty, "");
    free(empty);

    return clings_report();
}
