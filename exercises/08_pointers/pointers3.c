// pointers3.c
//
// Pointer arithmetic: adding n to a pointer moves it n *elements* forward
// (not n bytes). For any array `arr`:
//
//     arr[i]  is exactly the same as  *(arr + i)
//
// Subtracting two pointers into the same array gives the number of elements
// between them.
//
// Fill in the FIXMEs, then implement `sum_range` using only pointers
// (no [] indexing!).

// I AM NOT DONE

#include <stddef.h>

#include "clings.h"

// Sums the elements from `begin` up to, but not including, `end`.
int sum_range(const int *begin, const int *end) {
    int total = 0;
    // TODO: walk a pointer from begin to end
    return total;
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;            // same as &arr[0]

    CHECK_INT(*p, FIXME);
    CHECK_INT(*(p + 2), FIXME);

    p++;
    CHECK_INT(*p, FIXME);
    CHECK_INT(p[2], FIXME);

    int *last = &arr[4];
    CHECK_INT(last - p, FIXME);

    CHECK_INT(sum_range(arr, arr + 5), 150);
    CHECK_INT(sum_range(arr + 1, arr + 3), 50);
    CHECK_INT(sum_range(arr, arr), 0);

    return clings_report();
}
