// pointers3.c - solution

#include <stddef.h>

#include "clings.h"

int sum_range(const int *begin, const int *end) {
    int total = 0;
    for (const int *p = begin; p != end; p++) {
        total += *p;
    }
    return total;
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;

    CHECK_INT(*p, 10);
    CHECK_INT(*(p + 2), 30);

    p++;
    CHECK_INT(*p, 20);
    CHECK_INT(p[2], 40);

    int *last = &arr[4];
    CHECK_INT(last - p, 3);

    CHECK_INT(sum_range(arr, arr + 5), 150);
    CHECK_INT(sum_range(arr + 1, arr + 3), 50);
    CHECK_INT(sum_range(arr, arr), 0);

    return clings_report();
}
