// files1.c - solution

#include <stdio.h>
#include <string.h>

#include "clings.h"

int main(void) {
    FILE *f = tmpfile();
    CHECK(f != NULL);
    if (f == NULL) {
        return clings_report();
    }

    fprintf(f, "apples %d\n", 3);
    fprintf(f, "pears %d\n", 5);
    fprintf(f, "plums %d\n", 11);

    rewind(f);

    char line[64];
    int lines = 0;
    char first[64] = "";
    while (fgets(line, sizeof(line), f) != NULL) {
        if (lines == 0) {
            strcpy(first, line);
        }
        lines++;
    }

    CHECK_INT(lines, 3);
    CHECK_STR(first, "apples 3\n");

    fclose(f);
    return clings_report();
}
