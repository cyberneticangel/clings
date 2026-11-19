// macros1.c - solution

#include "clings.h"

#define SQUARE(x) ((x) * (x))
#define ADD(a, b) ((a) + (b))
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(void) {
    CHECK_INT(SQUARE(3), 9);
    CHECK_INT(SQUARE(1 + 2), 9);
    CHECK_INT(100 / SQUARE(5), 4);

    CHECK_INT(ADD(2, 3) * 10, 50);

    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    CHECK_INT(ARRAY_LEN(nums), 7);

    return clings_report();
}
