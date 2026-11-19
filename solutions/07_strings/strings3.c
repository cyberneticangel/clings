// strings3.c - solution

#include <stddef.h>

#include "clings.h"

size_t my_strlen(const char *s) {
    size_t n = 0;
    while (s[n] != '\0') {
        n++;
    }
    return n;
}

void my_strcpy(char *dst, const char *src) {
    size_t i = 0;
    do {
        dst[i] = src[i];
    } while (src[i++] != '\0');
}

int count_char(const char *s, char c) {
    int count = 0;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            count++;
        }
    }
    return count;
}

int main(void) {
    CHECK_INT(my_strlen("hello"), 5);
    CHECK_INT(my_strlen(""), 0);

    char buf[32];
    my_strcpy(buf, "copy me");
    CHECK_STR(buf, "copy me");
    my_strcpy(buf, "hi");
    CHECK_STR(buf, "hi");

    CHECK_INT(count_char("mississippi", 's'), 4);
    CHECK_INT(count_char("mississippi", 'x'), 0);

    return clings_report();
}
