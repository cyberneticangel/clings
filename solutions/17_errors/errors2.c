// errors2.c - solution

#include <stdio.h>
#include <stdlib.h>

#include "clings.h"

typedef enum { OK = 0, ERR_NOMEM, ERR_PARSE } Error;

Error load_scores(FILE *f, size_t count, int **out) {
    Error err = ERR_NOMEM;
    char *line = NULL;
    int *scores = malloc(count * sizeof(*scores));
    if (scores == NULL) {
        goto fail;
    }
    line = malloc(64);
    if (line == NULL) {
        goto fail;
    }
    for (size_t i = 0; i < count; i++) {
        if (fgets(line, 64, f) == NULL || sscanf(line, "%d", &scores[i]) != 1) {
            err = ERR_PARSE;
            goto fail;
        }
    }
    free(line);
    *out = scores;
    return OK;

fail:
    free(line);
    free(scores);
    return err;
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
    CHECK_INT(load_scores(f, 10, &bad), ERR_PARSE);
    CHECK(bad == NULL);

    fclose(f);
    return clings_report();
}
