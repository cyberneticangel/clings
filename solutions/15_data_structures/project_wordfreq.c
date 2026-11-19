// project_wordfreq.c - solution

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "clings.h"

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry **buckets;
    size_t bucket_count;
    size_t size;
} Map;

static unsigned long hash(const char *s) {
    unsigned long h = 5381;
    for (; *s != '\0'; s++) {
        h = h * 33 + (unsigned char)*s;
    }
    return h;
}

Map *map_new(size_t buckets) {
    Map *m = malloc(sizeof(*m));
    if (m == NULL) {
        return NULL;
    }
    m->buckets = calloc(buckets, sizeof(*m->buckets));
    if (m->buckets == NULL) {
        free(m);
        return NULL;
    }
    m->bucket_count = buckets;
    m->size = 0;
    return m;
}

void map_free(Map *m) {
    if (m == NULL) {
        return;
    }
    for (size_t i = 0; i < m->bucket_count; i++) {
        Entry *e = m->buckets[i];
        while (e != NULL) {
            Entry *next = e->next;
            free(e->key);
            free(e);
            e = next;
        }
    }
    free(m->buckets);
    free(m);
}

int *map_get(Map *m, const char *key) {
    size_t b = hash(key) % m->bucket_count;
    for (Entry *e = m->buckets[b]; e != NULL; e = e->next) {
        if (strcmp(e->key, key) == 0) {
            return &e->value;
        }
    }
    return NULL;
}

bool map_increment(Map *m, const char *key) {
    int *v = map_get(m, key);
    if (v != NULL) {
        (*v)++;
        return true;
    }
    Entry *e = malloc(sizeof(*e));
    if (e == NULL) {
        return false;
    }
    size_t len = strlen(key);
    e->key = malloc(len + 1);
    if (e->key == NULL) {
        free(e);
        return false;
    }
    memcpy(e->key, key, len + 1);
    e->value = 1;
    size_t b = hash(key) % m->bucket_count;
    e->next = m->buckets[b];
    m->buckets[b] = e;
    m->size++;
    return true;
}

bool count_words(Map *m, const char *text) {
    char word[64];
    size_t len = 0;
    for (const char *p = text;; p++) {
        unsigned char c = (unsigned char)*p;
        if (isalpha(c)) {
            if (len + 1 < sizeof(word)) {
                word[len++] = (char)tolower(c);
            }
        } else {
            if (len > 0) {
                word[len] = '\0';
                if (!map_increment(m, word)) {
                    return false;
                }
                len = 0;
            }
            if (c == '\0') {
                break;
            }
        }
    }
    return true;
}

const char *most_common(const Map *m, int *count) {
    const char *best = NULL;
    *count = 0;
    for (size_t i = 0; i < m->bucket_count; i++) {
        for (const Entry *e = m->buckets[i]; e != NULL; e = e->next) {
            if (e->value > *count) {
                *count = e->value;
                best = e->key;
            }
        }
    }
    return best;
}

int main(void) {
    Map *m = map_new(8);
    CHECK(m != NULL);
    if (m == NULL) {
        return clings_report();
    }

    CHECK(map_get(m, "nothing") == NULL);

    CHECK(map_increment(m, "apple"));
    CHECK(map_increment(m, "apple"));
    CHECK(map_increment(m, "pear"));
    int *apple = map_get(m, "apple");
    CHECK(apple != NULL);
    if (apple) {
        CHECK_INT(*apple, 2);
    }
    CHECK_INT(m->size, 2);

    char key[] = "temp";
    CHECK(map_increment(m, key));
    key[0] = 'X';
    CHECK(map_get(m, "temp") != NULL);
    map_free(m);

    m = map_new(16);
    if (m == NULL) {
        return clings_report();
    }
    const char *text =
        "It was the best of times, it was the worst of times, it was the age "
        "of wisdom, it was the age of foolishness, it was the epoch of belief";
    CHECK(count_words(m, text));

    int *the = map_get(m, "the");
    CHECK(the != NULL && *the == 5);
    int *it = map_get(m, "it");
    CHECK(it != NULL && *it == 5);
    CHECK(map_get(m, "It") == NULL);
    CHECK_INT(m->size, 12);

    int top = 0;
    const char *word = most_common(m, &top);
    CHECK_INT(top, 5);
    CHECK(word != NULL);

    map_free(m);
    return clings_report();
}
