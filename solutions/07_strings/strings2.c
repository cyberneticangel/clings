// strings2.c - solution

#include <stdbool.h>
#include <string.h>

#include "clings.h"

bool is_yes(const char *answer) {
    return strcmp(answer, "yes") == 0;
}

const char *first_alphabetically(const char *a, const char *b) {
    if (strcmp(a, b) < 0) {
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
