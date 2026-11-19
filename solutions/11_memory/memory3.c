// memory3.c - solution

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
    b->values = NULL;
    b->len = 0;
}

int main(void) {
    Buffer b = buffer_new(4);
    b.values[2] = 42;

    CHECK_INT(b.values[2], 42);
    buffer_free(&b);

    buffer_free(&b);
    CHECK(b.values == NULL);
    CHECK_INT(b.len, 0);

    return clings_report();
}
