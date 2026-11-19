// strings4.c
//
// A string literal like "hello" lives in read-only memory. When you write
//
//     char *s = "hello";
//
// `s` points straight at that read-only memory, and modifying it crashes
// (or worse). But
//
//     char s[] = "hello";
//
// creates a brand new array on the stack and *copies* the characters into it.
// That copy is yours to modify.
//
// The functions are correct. Fix main.

// I AM NOT DONE

#include <ctype.h>
#include <string.h>

#include "clings.h"

void shout(char *s) {
    for (size_t i = 0; s[i] != '\0'; i++) {
        s[i] = (char)toupper((unsigned char)s[i]);
    }
}

void reverse(char *s) {
    size_t len = strlen(s);
    for (size_t i = 0; i < len / 2; i++) {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

int main(void) {
    char *word = "hello";
    shout(word);
    CHECK_STR(word, "HELLO");

    char *other = "stressed";
    reverse(other);
    CHECK_STR(other, "desserts");

    return clings_report();
}
