// memory5.c - solution

#include <stdbool.h>
#include <stdlib.h>

#include "clings.h"

typedef struct {
    int *data;
    size_t len;
    size_t cap;
} Vec;

bool vec_push(Vec *v, int value) {
    if (v->len == v->cap) {
        size_t new_cap = v->cap == 0 ? 4 : v->cap * 2;
        int *bigger = realloc(v->data, new_cap * sizeof(*bigger));
        if (bigger == NULL) {
            return false;
        }
        v->data = bigger;
        v->cap = new_cap;
    }
    v->data[v->len++] = value;
    return true;
}

void vec_free(Vec *v) {
    free(v->data);
    v->data = NULL;
    v->len = 0;
    v->cap = 0;
}

int main(void) {
    Vec v = {0};

    for (int i = 0; i < 100; i++) {
        CHECK(vec_push(&v, i * 10));
    }
    CHECK_INT(v.len, 100);
    CHECK(v.cap >= 100);
    CHECK_INT(v.data[0], 0);
    CHECK_INT(v.data[57], 570);
    CHECK_INT(v.data[99], 990);

    vec_free(&v);
    CHECK(v.data == NULL);
    CHECK_INT(v.len, 0);
    CHECK_INT(v.cap, 0);

    CHECK(vec_push(&v, 7));
    CHECK_INT(v.data[0], 7);
    vec_free(&v);

    return clings_report();
}
