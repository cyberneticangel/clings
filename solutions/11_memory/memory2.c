// memory2.c - solution

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
        free(tmp);
    }

    free(a);
    free(b);
    return clings_report();
}
