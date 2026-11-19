// pointers6.c - solution

#include <stddef.h>

#include "clings.h"

void point_at_largest(int *arr, size_t len, int **out) {
    *out = &arr[0];
    for (size_t i = 1; i < len; i++) {
        if (arr[i] > **out) {
            *out = &arr[i];
        }
    }
}

int main(void) {
    int scores[] = {55, 92, 78, 92, 13};
    int *best = NULL;

    point_at_largest(scores, 5, &best);
    CHECK(best != NULL);
    CHECK(best == &scores[1]);

    *best += 1;
    CHECK_INT(scores[1], 93);

    return clings_report();
}
