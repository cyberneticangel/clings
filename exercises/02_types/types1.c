// types1.c
//
// C has several basic types:
//
//     char     - a single byte, often used for characters ('a', 'Z', '\n')
//     int      - a whole number (usually 32 bits)
//     long     - a bigger whole number (64 bits on most 64-bit Linux/macOS)
//     float    - a single-precision floating point number
//     double   - a double-precision floating point number (use this one)
//
// `sizeof` tells you how many bytes something takes up.
// The C standard guarantees sizeof(char) is always 1; the rest vary between
// platforms. The values checked here are true on typical x86-64 and ARM64
// machines.
//
// Fill in the FIXMEs.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    CHECK_INT(sizeof(char), FIXME);
    CHECK_INT(sizeof(int), FIXME);
    CHECK_INT(sizeof(double), FIXME);

    // A char is just a small number. Characters are stored using their
    // ASCII code: 'A' is 65, 'B' is 66, ...
    char letter = 'A';
    CHECK_INT(letter, 65);
    CHECK_INT(letter + 2, FIXME);  // which letter is this? use the 'X' syntax

    double pi = 3.14159;
    CHECK_DBL(pi * 2, FIXME);

    return clings_report();
}
