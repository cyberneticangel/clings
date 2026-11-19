// memory1.c - solution

#include <stdlib.h>

#include "clings.h"

int *squares(size_t n) {
    int *arr = malloc(n * sizeof(*arr));
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
