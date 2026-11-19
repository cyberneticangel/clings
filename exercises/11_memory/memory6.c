// memory6.c
//
// malloc gives you uninitialized memory. calloc(count, size) allocates
// count * size bytes AND sets them all to zero. Use calloc when you need
// a zeroed array (it also checks count * size for overflow).
//
// `letter_histogram` counts how often each letter a-z appears in text.
// The counts come out as garbage. Fix it.

// I AM NOT DONE

#include <ctype.h>
#include <stdlib.h>

#include "clings.h"

// Returns a heap array of 26 counts: [0] for 'a', [1] for 'b', ...
int *letter_histogram(const char *text) {
    int *counts = malloc(26 * sizeof(*counts));
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
