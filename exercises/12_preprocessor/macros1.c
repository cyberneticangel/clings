// macros1.c
//
// Lines starting with `#` are handled by the *preprocessor*, which runs
// before the compiler and does plain text substitution.
//
//     #define MAX_USERS 100            // object-like macro: a constant
//     #define DOUBLE(x) ((x) * 2)      // function-like macro
//
// Because macros are text substitution, not real functions, they have
// pitfalls. SQUARE(1 + 2) expands to  1 + 2 * 1 + 2  which is 5, not 9!
// The fix: wrap every parameter AND the whole body in parentheses.
//
// Fix the macros so the checks pass.

// I AM NOT DONE

#include "clings.h"

#define SQUARE(x) x * x
#define ADD(a, b) a + b
#define ARRAY_LEN(arr) FIXME

int main(void) {
    CHECK_INT(SQUARE(3), 9);
    CHECK_INT(SQUARE(1 + 2), 9);
    CHECK_INT(100 / SQUARE(5), 4);

    CHECK_INT(ADD(2, 3) * 10, 50);

    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    CHECK_INT(ARRAY_LEN(nums), 7);

    return clings_report();
}
