// project_strbuf.c - solution

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

static bool sb_reserve(StrBuf *sb, size_t extra) {
    size_t needed = sb->len + extra + 1;
    if (needed <= sb->cap) {
        return true;
    }
    size_t new_cap = sb->cap == 0 ? 16 : sb->cap;
    while (new_cap < needed) {
        new_cap *= 2;
    }
    char *p = realloc(sb->data, new_cap);
    if (p == NULL) {
        return false;
    }
    sb->data = p;
    sb->cap = new_cap;
    return true;
}

bool sb_append(StrBuf *sb, const char *s) {
    size_t n = strlen(s);
    if (!sb_reserve(sb, n)) {
        return false;
    }
    memcpy(sb->data + sb->len, s, n + 1);
    sb->len += n;
    return true;
}

bool sb_append_char(StrBuf *sb, char c) {
    if (!sb_reserve(sb, 1)) {
        return false;
    }
    sb->data[sb->len++] = c;
    sb->data[sb->len] = '\0';
    return true;
}

bool sb_append_int(StrBuf *sb, long value) {
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%ld", value);
    return sb_append(sb, tmp);
}

void sb_free(StrBuf *sb) {
    free(sb->data);
    sb->data = NULL;
    sb->len = 0;
    sb->cap = 0;
}

char **split_words(const char *s, size_t *count) {
    size_t cap = 4, n = 0;
    char **words = malloc(cap * sizeof(*words));
    if (words == NULL) {
        *count = 0;
        return NULL;
    }
    const char *p = s;
    while (*p != '\0') {
        while (*p == ' ') {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        const char *start = p;
        while (*p != '\0' && *p != ' ') {
            p++;
        }
        size_t len = (size_t)(p - start);

        if (n == cap) {
            char **bigger = realloc(words, cap * 2 * sizeof(*words));
            if (bigger == NULL) {
                break;
            }
            words = bigger;
            cap *= 2;
        }
        char *word = malloc(len + 1);
        if (word == NULL) {
            break;
        }
        memcpy(word, start, len);
        word[len] = '\0';
        words[n++] = word;
    }
    *count = n;
    return words;
}

void free_words(char **words, size_t count) {
    if (words == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

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
