// strings3.c
//
// To really understand strings, write the library functions yourself!
// Don't use anything from <string.h> here.
//
//   my_strlen(s)        - count characters until the '\0'
//   my_strcpy(dst, src) - copy src into dst, INCLUDING the '\0'
//   count_char(s, c)    - how many times c appears in s

// I AM NOT DONE

#include <stddef.h>

#include "clings.h"

size_t my_strlen(const char *s) {
    // TODO
}

void my_strcpy(char *dst, const char *src) {
    // TODO
}

int count_char(const char *s, char c) {
    // TODO
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
