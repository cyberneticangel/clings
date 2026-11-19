// errors2.c
//
// When a function acquires several resources (memory, files, ...) and any
// step can fail, every failure path must release whatever was acquired so
// far. Copy-pasting the cleanup into every `if` gets messy and buggy fast.
//
// The idiomatic C solution is a single cleanup section at the end of the
// function, reached with `goto`:
//
//     int do_work(void) {
//         int result = -1;
//         char *a = malloc(...);
//         if (!a) goto out;
//         char *b = malloc(...);
//         if (!b) goto free_a;
//         ...
//         result = 0;
//         free(b);
//     free_a:
//         free(a);
//     out:
//         return result;
//     }
//
// `load_scores` leaks on its error paths. Restructure it with goto-cleanup
// (or any other way you like) so nothing leaks.

// I AM NOT DONE

#include <stdio.h>
#include <stdlib.h>

#include "clings.h"

typedef enum { OK = 0, ERR_NOMEM, ERR_PARSE } Error;

// Reads `count` integers (one per line) from f into a new heap array.
// On success, stores the array in *out and returns OK.
// On failure, returns an error code and frees everything it allocated.
Error load_scores(FILE *f, size_t count, int **out) {
    int *scores = malloc(count * sizeof(*scores));
    if (scores == NULL) {
        return ERR_NOMEM;
    }
    char *line = malloc(64);
    if (line == NULL) {
        return ERR_NOMEM;
    }
    for (size_t i = 0; i < count; i++) {
        if (fgets(line, 64, f) == NULL || sscanf(line, "%d", &scores[i]) != 1) {
            return ERR_PARSE;
        }
    }
    free(line);
    *out = scores;
    return OK;
}

int main(void) {
    FILE *f = tmpfile();
    if (f == NULL) {
        perror("tmpfile");
        return 1;
    }
    fputs("10\n20\n30\nnope\n", f);

    int *scores = NULL;
    rewind(f);
    CHECK_INT(load_scores(f, 3, &scores), OK);
    if (scores != NULL) {
        CHECK_INT(scores[0] + scores[1] + scores[2], 60);
        free(scores);
    }

    int *bad = NULL;
    rewind(f);
    CHECK_INT(load_scores(f, 4, &bad), ERR_PARSE);
    CHECK(bad == NULL);

    rewind(f);
    CHECK_INT(load_scores(f, 10, &bad), ERR_PARSE);   // runs out of lines
    CHECK(bad == NULL);

    fclose(f);
    return clings_report();
}
