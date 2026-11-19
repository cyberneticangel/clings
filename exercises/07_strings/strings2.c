// strings2.c
//
// Since a string is an array (and arrays decay to pointers), `==` on two
// strings compares their *addresses*, not their contents!
//
// To compare contents, use strcmp from <string.h>:
//     strcmp(a, b) == 0   when the strings are equal
//     strcmp(a, b) <  0   when a sorts before b
//     strcmp(a, b) >  0   when a sorts after b
//
// Fix both functions.

// I AM NOT DONE

#include <stdbool.h>
#include <string.h>

#include "clings.h"

bool is_yes(const char *answer) {
    return answer == "yes";
}

// Returns whichever word comes first in alphabetical order.
const char *first_alphabetically(const char *a, const char *b) {
    if (a < b) {
        return a;
    }
    return b;
}

int main(void) {
    char typed[] = "yes";
    CHECK(is_yes(typed));
    CHECK(!is_yes("no"));

    char apple[] = "apple";
    char banana[] = "banana";
    CHECK_STR(first_alphabetically(banana, apple), "apple");
    CHECK_STR(first_alphabetically(apple, banana), "apple");
    CHECK_STR(first_alphabetically("zebra", "yak"), "yak");

    return clings_report();
}
