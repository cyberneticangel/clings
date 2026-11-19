// pointers4.c
//
// NULL is a special pointer value meaning "points to nothing". Dereferencing
// NULL crashes your program (if you're lucky).
//
// Functions that search for something often return NULL when it isn't found,
// so the caller MUST check before using the result.
//
// Implement `find`, then fix main so it doesn't crash.

// I AM NOT DONE

#include <stddef.h>

#include "clings.h"

// Returns a pointer to the first element equal to `target`, or NULL.
int *find(int *arr, size_t len, int target) {
    // TODO
}

int main(void) {
    int data[] = {3, 1, 4, 1, 5, 9, 2, 6};

    int *four = find(data, 8, 4);
    CHECK(four == &data[2]);

    // Because `find` returns a pointer INTO the array, we can modify it.
    *four = 40;
    CHECK_INT(data[2], 40);

    int *missing = find(data, 8, 7);
    CHECK(missing == NULL);

    int found_value = *missing;  // uh oh
    CHECK_INT(found_value, -1);  // -1 means "not found"

    return clings_report();
}
