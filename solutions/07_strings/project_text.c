// project_text.c - solution

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "clings.h"

int word_count(const char *s) {
    int count = 0;
    bool in_word = false;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (isspace((unsigned char)s[i])) {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            count++;
        }
    }
    return count;
}

void capitalize_words(char *s) {
    bool start = true;
    for (size_t i = 0; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char)s[i];
        if (isspace(c)) {
            start = true;
        } else {
            s[i] = (char)(start ? toupper(c) : tolower(c));
            start = false;
        }
    }
}

bool is_palindrome(const char *s) {
    size_t len = strlen(s);
    if (len == 0) {
        return true;
    }
    size_t i = 0, j = len - 1;
    while (i < j) {
        if (!isalpha((unsigned char)s[i])) {
            i++;
        } else if (!isalpha((unsigned char)s[j])) {
            j--;
        } else {
            if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j])) {
                return false;
            }
            i++;
            j--;
        }
    }
    return true;
}

void caesar(char *s, int shift) {
    shift = (shift % 26 + 26) % 26;
    for (size_t i = 0; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char)s[i];
        if (isupper(c)) {
            s[i] = (char)('A' + (c - 'A' + shift) % 26);
        } else if (islower(c)) {
            s[i] = (char)('a' + (c - 'a' + shift) % 26);
        }
    }
}

int main(void) {
    CHECK_INT(word_count("hello world"), 2);
    CHECK_INT(word_count("  hi   there "), 2);
    CHECK_INT(word_count(""), 0);
    CHECK_INT(word_count("one"), 1);

    char title[] = "hELLO wORLD, it's   C time";
    capitalize_words(title);
    CHECK_STR(title, "Hello World, It's   C Time");

    CHECK(is_palindrome("racecar"));
    CHECK(is_palindrome("A man, a plan, a canal: Panama!"));
    CHECK(!is_palindrome("clings"));
    CHECK(is_palindrome(""));

    char secret[] = "Hello, World!";
    caesar(secret, 3);
    CHECK_STR(secret, "Khoor, Zruog!");
    caesar(secret, -3);
    CHECK_STR(secret, "Hello, World!");

    char wrap[] = "xyz XYZ";
    caesar(wrap, 4);
    CHECK_STR(wrap, "bcd BCD");

    return clings_report();
}
