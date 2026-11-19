// pointers5.c
//
// Local variables live on the *stack*, and disappear when their function
// returns. Returning a pointer to a local variable gives the caller a
// "dangling pointer" to memory that no longer belongs to anyone.
//
// A common, safe pattern instead: the CALLER provides the buffer, and the
// function fills it in.
//
// Change `make_greeting` to write into a buffer supplied by the caller:
//
//     void make_greeting(char *out, size_t out_size, const char *name)

// I AM NOT DONE

#include <stdio.h>

#include "clings.h"

char *make_greeting(const char *name) {
    char buf[64];
    snprintf(buf, sizeof(buf), "Hello, %s!", name);
    return buf;
}

int main(void) {
    char *g = make_greeting("World");
    CHECK_STR(g, "Hello, World!");

    return clings_report();
}
