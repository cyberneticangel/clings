// arrays3.c
//
// When you pass an array to a function, the function does NOT receive a copy
// of the array. It receives a *pointer to its first element* (the array
// "decays" to a pointer). The size information is lost: inside the function,
// sizeof(arr) is just the size of a pointer!
//
// That's why C functions that take arrays almost always take a length, too.
//
// Fix `sum` (and the calls to it) by adding a length parameter.
// Use `size_t`, the standard unsigned type for sizes and counts.

// I AM NOT DONE

#include <stddef.h>

#include "clings.h"

int sum(int arr[]) {
    int total = 0;
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        total += arr[i];
    }
    return total;
}

int main(void) {
    int small[3] = {1, 2, 3};
    int big[8] = {1, 1, 1, 1, 1, 1, 1, 10};

    CHECK_INT(sum(small), 6);
    CHECK_INT(sum(big), 17);

    return clings_report();
}
