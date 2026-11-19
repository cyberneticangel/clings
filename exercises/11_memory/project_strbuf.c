// project_strbuf.c - PROJECT: A growable string builder + split
//
// Fixed-size char buffers are a constant source of bugs. Build a string
// type that grows itself, plus a function that splits a string into
// separately allocated pieces.
//
//   StrBuf: { char *data; size_t len; size_t cap; }
//     data is always '\0'-terminated (when not NULL), len excludes the '\0'.
//
//   bool sb_append(StrBuf *sb, const char *s)
//   bool sb_append_char(StrBuf *sb, char c)
//   bool sb_append_int(StrBuf *sb, long value)    (hint: snprintf)
//   void sb_free(StrBuf *sb)                       resets to {0}
//       The appends grow the buffer as needed (double the capacity),
//       and return false if memory runs out.
//
//   char **split_words(const char *s, size_t *count)
//       Returns a heap array of heap strings: one per space-separated word.
//       Stores the number of words in *count.
//   void free_words(char **words, size_t count)
//       Frees every word and the array itself.
//
// Tip: write a helper `static bool sb_reserve(StrBuf *sb, size_t extra)`
// that makes sure there is room for `extra` more chars plus the '\0'.

// I AM NOT DONE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clings.h"

typedef struct {
    char *data;
    size_t len;
    size_t cap;
} StrBuf;

// Write your functions here.

int main(void) {
    StrBuf sb = {0};

    CHECK(sb_append(&sb, "Hello"));
    CHECK(sb_append_char(&sb, ','));
    CHECK(sb_append(&sb, " world"));
    CHECK_STR(sb.data, "Hello, world");
    CHECK_INT(sb.len, 12);

    for (int i = 0; i < 1000; i++) {
        CHECK(sb_append_char(&sb, '!'));
    }
    CHECK_INT(sb.len, 1012);
    CHECK(sb.cap > sb.len);
    CHECK_INT(sb.data[sb.len], '\0');
    sb_free(&sb);
    CHECK(sb.data == NULL);

    sb_append(&sb, "answer=");
    sb_append_int(&sb, 42);
    sb_append(&sb, " min=");
    sb_append_int(&sb, -9223372036854775807L - 1);
    CHECK_STR(sb.data, "answer=42 min=-9223372036854775808");
    sb_free(&sb);

    size_t count = 0;
    char **words = split_words("  the quick  brown fox ", &count);
    CHECK_INT(count, 4);
    if (words != NULL && count == 4) {
        CHECK_STR(words[0], "the");
        CHECK_STR(words[1], "quick");
        CHECK_STR(words[3], "fox");
    }
    free_words(words, count);

    words = split_words("", &count);
    CHECK_INT(count, 0);
    free_words(words, count);

    return clings_report();
}
