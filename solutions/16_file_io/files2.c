// files2.c - solution

#include <stdio.h>

#include "clings.h"

int total_quantity(FILE *f, int *bad_lines) {
    char line[128];
    char name[32];
    int qty;
    int total = 0;
    *bad_lines = 0;
    while (fgets(line, sizeof(line), f) != NULL) {
        if (sscanf(line, "%31s %d", name, &qty) == 2) {
            total += qty;
        } else {
            (*bad_lines)++;
        }
    }
    return total;
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
