// pointers5.c - solution

#include <stdio.h>

#include "clings.h"

void make_greeting(char *out, size_t out_size, const char *name) {
    snprintf(out, out_size, "Hello, %s!", name);
}

int main(void) {
    char g[64];
    make_greeting(g, sizeof(g), "World");
    CHECK_STR(g, "Hello, World!");

    return clings_report();
}
