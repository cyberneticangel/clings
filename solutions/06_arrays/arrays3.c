// arrays3.c - solution

#include <stddef.h>

#include "clings.h"

int sum(const int arr[], size_t len) {
    int total = 0;
    for (size_t i = 0; i < len; i++) {
        total += arr[i];
    }
    return total;
}

#define LEN(a) (sizeof(a) / sizeof((a)[0]))

int main(void) {
    int small[3] = {1, 2, 3};
    int big[8] = {1, 1, 1, 1, 1, 1, 1, 10};

    CHECK_INT(sum(small, LEN(small)), 6);
    CHECK_INT(sum(big, LEN(big)), 17);

    return clings_report();
}
