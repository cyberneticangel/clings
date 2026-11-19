// memory6.c - solution

#include <ctype.h>
#include <stdlib.h>

#include "clings.h"

int *letter_histogram(const char *text) {
    int *counts = calloc(26, sizeof(*counts));
    if (counts == NULL) {
        return NULL;
    }
    for (size_t i = 0; text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)tolower((unsigned char)text[i]);
        if (c >= 'a' && c <= 'z') {
            counts[c - 'a']++;
        }
    }
    return counts;
}

int main(void) {
    int *h = letter_histogram("Hello, World!");
    CHECK(h != NULL);
    CHECK_INT(h['l' - 'a'], 3);
    CHECK_INT(h['o' - 'a'], 2);
    CHECK_INT(h['h' - 'a'], 1);
    CHECK_INT(h['z' - 'a'], 0);
    free(h);

    return clings_report();
}
