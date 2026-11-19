// memory4.c - solution

#include <stdlib.h>
#include <string.h>

#include "clings.h"

char *my_strdup(const char *s) {
    char *copy = malloc(strlen(s) + 1);
    if (copy != NULL) {
        strcpy(copy, s);
    }
    return copy;
}

char *concat(const char *a, const char *b) {
    size_t la = strlen(a), lb = strlen(b);
    char *out = malloc(la + lb + 1);
    if (out == NULL) {
        return NULL;
    }
    memcpy(out, a, la);
    memcpy(out + la, b, lb + 1); // includes b's '\0'
    return out;
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
