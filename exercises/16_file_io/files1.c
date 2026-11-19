// files1.c
//
// Files are accessed through a `FILE *` handle from <stdio.h>:
//
//     FILE *f = fopen("notes.txt", "w");   // "r" read, "w" write, "a" append
//     if (f == NULL) { perror("fopen"); return 1; }
//     fprintf(f, "score: %d\n", 42);       // like printf, but into the file
//     fclose(f);                           // flush and release the handle
//
//     fgets(buf, sizeof(buf), f)  reads one line (including the '\n'),
//                                 returns NULL at end of file.
//
// Here we use tmpfile(), which creates a temporary file opened for both
// reading and writing that's deleted automatically when closed.
// rewind(f) moves back to the beginning so we can read what we wrote.
//
// Fill in the TODOs. Not closing the file leaks memory. LeakSanitizer
// will notice!

// I AM NOT DONE

#include <stdio.h>
#include <string.h>

#include "clings.h"

int main(void) {
    FILE *f = tmpfile();
    CHECK(f != NULL);
    if (f == NULL) {
        return clings_report();
    }

    // TODO: write these three lines to f with fprintf:
    //   apples 3
    //   pears 5
    //   plums 11

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

    return clings_report();
}
