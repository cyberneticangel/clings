// pointers2.c - solution

#include "clings.h"

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void min_max(const int arr[], size_t len, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    for (size_t i = 1; i < len; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

int main(void) {
    int a = 1, b = 2;
    swap(&a, &b);
    CHECK_INT(a, 2);
    CHECK_INT(b, 1);

    int nums[] = {4, -2, 9, 0, 7};
    int lo, hi;
    min_max(nums, 5, &lo, &hi);
    CHECK_INT(lo, -2);
    CHECK_INT(hi, 9);

    return clings_report();
}
