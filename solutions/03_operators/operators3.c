// operators3.c - solution

#include <stdbool.h>

#include "clings.h"

bool is_between(int x, int low, int high) {
    return low < x && x < high;
}

bool is_answer(int n) {
    if (n == 42) {
        return true;
    }
    return false;
}

int main(void) {
    CHECK(is_between(5, 1, 10));
    CHECK(!is_between(15, 1, 10));
    CHECK(!is_between(-3, 1, 10));

    CHECK(is_answer(42));
    CHECK(!is_answer(41));

    CHECK_INT(3 > 2, 1);
    CHECK_INT(3 < 2, 0);
    CHECK_INT(!0, 1);
    CHECK_INT(!7, 0);

    return clings_report();
}
