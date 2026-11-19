// memory1.c
//
// So far everything lived on the stack, with sizes fixed at compile time.
// The *heap* lets you allocate memory at runtime, of any size:
//
//     #include <stdlib.h>
//     int *nums = malloc(count * sizeof(int));   // or: sizeof(*nums)
//     ...
//     free(nums);    // give it back when you're done!
//
// malloc takes a size in BYTES and returns a pointer, or NULL if it fails.
// Memory from malloc is NOT initialized: it contains garbage until you
// write to it.
//
// `squares(n)` should return a heap array containing 0, 1, 4, 9, ...
// AddressSanitizer reports a "heap-buffer-overflow". Fix it.

// I AM NOT DONE

#include <stdlib.h>

#include "clings.h"

int *squares(size_t n) {
    int *arr = malloc(n);
    if (arr == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < n; i++) {
        arr[i] = (int)(i * i);
    }
    return arr;
}

int main(void) {
    int *sq = squares(10);
    CHECK(sq != NULL);
    CHECK_INT(sq[0], 0);
    CHECK_INT(sq[3], 9);
    CHECK_INT(sq[9], 81);
    free(sq);

    return clings_report();
}
