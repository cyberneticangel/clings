// strings4.c - solution

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
    char word[] = "hello";
    shout(word);
    CHECK_STR(word, "HELLO");

    char other[] = "stressed";
    reverse(other);
    CHECK_STR(other, "desserts");

    return clings_report();
}
