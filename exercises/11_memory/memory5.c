// memory5.c
//
// A growable array (like a C++ vector or a Rust Vec) is built from malloc
// and `realloc`. realloc resizes an allocation, possibly moving it:
//
//     int *bigger = realloc(old, new_size_in_bytes);
//     if (bigger == NULL) { /* old is still valid! handle the error */ }
//     old = bigger;
//
// The usual strategy: keep a `capacity` and double it when the array fills
// up, so that pushing is fast on average.
//
// Implement `vec_push` and `vec_free`.

// I AM NOT DONE

#include <stdbool.h>
#include <stdlib.h>

#include "clings.h"

typedef struct {
    int *data;
    size_t len;
    size_t cap;
} Vec;

// Appends value to the end, growing the storage if needed.
// Returns false if memory couldn't be allocated.
bool vec_push(Vec *v, int value) {
    // TODO
}

// Frees the storage and resets v to an empty vec.
void vec_free(Vec *v) {
    // TODO
}

int main(void) {
    Vec v = {0}; // data = NULL, len = 0, cap = 0

    for (int i = 0; i < 100; i++) {
        CHECK(vec_push(&v, i * 10));
    }
    CHECK_INT(v.len, 100);
    CHECK(v.cap >= 100);
    CHECK_INT(v.data[0], 0);
    CHECK_INT(v.data[57], 570);
    CHECK_INT(v.data[99], 990);

    vec_free(&v);
    CHECK(v.data == NULL);
    CHECK_INT(v.len, 0);
    CHECK_INT(v.cap, 0);

    // A freed vec can be reused.
    CHECK(vec_push(&v, 7));
    CHECK_INT(v.data[0], 7);
    vec_free(&v);

    return clings_report();
}
