// strings1.c - solution

#include <string.h>

#include "clings.h"

int main(void) {
    char greeting[6] = "hello";
    char name[4] = {'B', 'o', 'b', '\0'};

    CHECK_INT(strlen(greeting), 5);
    CHECK_STR(greeting, "hello");
    CHECK_STR(name, "Bob");

    char auto_sized[] = "clings";
    CHECK_INT(sizeof(auto_sized), 7);
    CHECK_INT(strlen(auto_sized), 6);

    return clings_report();
}
