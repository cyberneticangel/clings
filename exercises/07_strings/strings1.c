// strings1.c
//
// C has no real string type. A "string" is just an array of chars that ends
// with a special *null terminator* character, '\0' (the byte value 0).
// That's how functions like strlen and printf know where the string ends.
//
//     char word[] = "cat";   // 4 bytes: 'c' 'a' 't' '\0'
//
// So a char array needs room for one more byte than the visible characters!
//
// Fix the array sizes.

// I AM NOT DONE

#include <string.h>

#include "clings.h"

int main(void) {
    char greeting[5] = "hello";
    char name[3] = {'B', 'o', 'b'};

    CHECK_INT(strlen(greeting), 5);
    CHECK_STR(greeting, "hello");
    CHECK_STR(name, "Bob");

    // sizeof counts the terminator; strlen doesn't.
    char auto_sized[] = "clings";
    CHECK_INT(sizeof(auto_sized), FIXME);
    CHECK_INT(strlen(auto_sized), FIXME);

    return clings_report();
}
