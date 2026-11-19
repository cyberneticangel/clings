// files2.c
//
// Reading structured data: read a line with fgets, then pull values out of it
// with sscanf, which is like scanf but reads from a string. It returns how
// many values it successfully parsed. ALWAYS check that number.
//
//     char name[32]; int qty;
//     if (sscanf(line, "%31s %d", name, &qty) == 2) { ... }
//
// The `31` in %31s limits how many chars are written, so name can't overflow.
//
// Implement `total_quantity`: read every line of `f`, parse "<name> <qty>",
// add up the quantities, and count lines that don't parse as errors.

// I AM NOT DONE

#include <stdio.h>

#include "clings.h"

// Returns the sum of all quantities; stores the number of bad lines in
// *bad_lines.
int total_quantity(FILE *f, int *bad_lines) {
    // TODO
}

int main(void) {
    FILE *f = tmpfile();
    if (f == NULL) {
        perror("tmpfile");
        return 1;
    }
    fputs("apples 3\n", f);
    fputs("pears 5\n", f);
    fputs("this line is garbage\n", f);
    fputs("plums 11\n", f);
    fputs("\n", f);
    rewind(f);

    int bad = -1;
    CHECK_INT(total_quantity(f, &bad), 19);
    CHECK_INT(bad, 2);

    fclose(f);
    return clings_report();
}
