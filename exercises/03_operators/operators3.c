// operators3.c
//
// Comparison operators:  ==  !=  <  >  <=  >=
// Logical operators:     &&  (and)   ||  (or)   !  (not)
//
// C has no separate boolean type in its oldest form: any non-zero value is
// "true" and 0 is "false". Comparisons evaluate to 1 or 0.
// (<stdbool.h> gives you `bool`, `true` and `false` as nicer names.)
//
// The two functions below contain classic mistakes that compile in C, but
// don't do what they look like. Our compiler flags turn them into errors.
// Fix them!

// I AM NOT DONE

#include <stdbool.h>

#include "clings.h"

// Returns true if x is strictly between low and high.
bool is_between(int x, int low, int high) {
    return low < x < high;
}

// Returns true if n is the answer to everything.
bool is_answer(int n) {
    if (n = 42) {
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
