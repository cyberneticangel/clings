// project_text.c - PROJECT: Text toolkit
//
// Write a handful of string utilities. You may use <string.h> and <ctype.h>
// (isalpha, isspace, toupper, tolower; cast chars to unsigned char before
// passing them to these).
//
//   int word_count(const char *s)
//       Words are runs of non-space characters. "  hi   there " has 2.
//
//   void capitalize_words(char *s)
//       Upper-case the first letter of every word, lower-case the rest.
//       "hELLO wORLD" -> "Hello World"
//
//   bool is_palindrome(const char *s)
//       Ignore case and anything that isn't a letter.
//       "A man, a plan, a canal: Panama!" is a palindrome.
//
//   void caesar(char *s, int shift)
//       Shift each letter by `shift` places in the alphabet, wrapping around
//       and keeping case. Non-letters are unchanged. shift may be negative
//       (that's how you decrypt) and between -25 and 25.
//       caesar("Hello, World!", 3) -> "Khoor, Zruog!"

// I AM NOT DONE

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "clings.h"

// Write your functions here.

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
