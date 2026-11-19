// arrays2.c
//
// C does NOT check array bounds. Reading or writing past the end of an array
// is undefined behavior: it may crash, silently corrupt other variables, or
// appear to work fine. That's why clings builds with AddressSanitizer, which
// reports out-of-bounds accesses.
//
// Run this, read the sanitizer's report (look for "stack-buffer-overflow"
// and the line number in YOUR file), then fix the bug.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    int squares[6];
    for (int i = 0; i <= 6; i++) {
        squares[i] = i * i;
    }

    CHECK_INT(squares[0], 0);
    CHECK_INT(squares[5], 25);

    return clings_report();
}
