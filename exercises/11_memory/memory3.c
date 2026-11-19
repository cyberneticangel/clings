// memory3.c
//
// After you free memory, the pointer still holds the old address, but the
// memory isn't yours anymore. Using it is a "use-after-free" bug, one of the
// most common sources of security vulnerabilities in C programs.
// Freeing the same memory twice ("double free") is just as bad.
//
// A good habit: set pointers to NULL right after freeing them.
// (free(NULL) is allowed and does nothing.)
//
// Fix the bugs AddressSanitizer reports. Don't remove any checks.

// I AM NOT DONE

#include <stdlib.h>

#include "clings.h"

typedef struct {
    int *values;
    size_t len;
} Buffer;

Buffer buffer_new(size_t len) {
    Buffer b = {.values = calloc(len, sizeof(int)), .len = len};
    return b;
}

void buffer_free(Buffer *b) {
    free(b->values);
}

int main(void) {
    Buffer b = buffer_new(4);
    b.values[2] = 42;

    buffer_free(&b);
    CHECK_INT(b.values[2], 42);

    // Freeing twice should be harmless...
    buffer_free(&b);
    CHECK(b.values == NULL);
    CHECK_INT(b.len, 0);

    return clings_report();
}
