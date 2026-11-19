// pointers4.c - solution

#include <stddef.h>

#include "clings.h"

int *find(int *arr, size_t len, int target) {
    for (size_t i = 0; i < len; i++) {
        if (arr[i] == target) {
            return &arr[i];
        }
    }
    return NULL;
}

int main(void) {
    int data[] = {3, 1, 4, 1, 5, 9, 2, 6};

    int *four = find(data, 8, 4);
    CHECK(four == &data[2]);

    *four = 40;
    CHECK_INT(data[2], 40);

    int *missing = find(data, 8, 7);
    CHECK(missing == NULL);

    int found_value = missing != NULL ? *missing : -1;
    CHECK_INT(found_value, -1);

    return clings_report();
}
