// pointers6.c
//
// Pointers can point to pointers! An `int **` is a pointer to an `int *`.
// You need one when a function must change *which thing* the caller's
// pointer points at.
//
// Also, `const` and pointers:
//     const int *p   - p points to a read-only int (can't do *p = ...)
//     int *const p   - p itself can't be changed to point elsewhere
//
// Implement `point_at_largest` so that it makes the caller's pointer point
// at the largest element.

// I AM NOT DONE

#include <stddef.h>

#include "clings.h"

void point_at_largest(int *arr, size_t len, int **out) {
    // TODO
}

int main(void) {
    int scores[] = {55, 92, 78, 92, 13};
    int *best = NULL;

    point_at_largest(scores, 5, &best);
    CHECK(best != NULL);
    CHECK(best == &scores[1]);   // the FIRST largest one

    // Bump the best score by 1 through the pointer.
    *best += 1;
    CHECK_INT(scores[1], 93);

    return clings_report();
}
