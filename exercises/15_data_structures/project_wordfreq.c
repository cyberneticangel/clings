// project_wordfreq.c - PROJECT: Hash map word counter
//
// A hash map stores key -> value pairs with (on average) constant-time
// lookups. The idea:
//   1. A *hash function* turns the key (a string) into a number.
//   2. hash % bucket_count picks a bucket.
//   3. Each bucket is a linked list ("chaining") of entries whose keys
//      landed there.
//
// Implement a string -> int map and use it to count words.
//
//   Map *map_new(size_t buckets)          (calloc is handy for the buckets)
//   void map_free(Map *m)                 frees all entries, keys, buckets, map
//   int *map_get(Map *m, const char *key) pointer to the value, or NULL
//   bool map_increment(Map *m, const char *key)
//       Adds 1 to key's count, inserting it with count 1 if missing.
//       The map must store its OWN copy of the key (malloc + copy).
//       Returns false if memory runs out.
//
// Then:
//   bool count_words(Map *m, const char *text)
//       Words are runs of letters (isalpha); count them lower-cased.
//       "The cat. THE end" -> the:2 cat:1 end:1
//
//   const char *most_common(const Map *m, int *count)
//       The key with the highest count (any one, if tied), storing its
//       count in *count. NULL if the map is empty.

// I AM NOT DONE

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
    size_t size;           // number of distinct keys
} Map;

// djb2, a simple and decent string hash function.
static unsigned long hash(const char *s) {
    unsigned long h = 5381;
    for (; *s != '\0'; s++) {
        h = h * 33 + (unsigned char)*s;
    }
    return h;
}

// Write your functions here.

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

    // the map keeps its own copy of the key
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
    CHECK(map_get(m, "It") == NULL);  // keys are lower-cased
    CHECK_INT(m->size, 12);

    int top = 0;
    const char *word = most_common(m, &top);
    CHECK_INT(top, 5);
    CHECK(word != NULL);

    map_free(m);
    return clings_report();
}
