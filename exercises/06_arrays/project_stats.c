// project_stats.c - PROJECT: Grade statistics
//
// A teacher has a list of exam scores (0-100). Write the functions that
// analyze them. Every function takes the array and its length.
//
//   double mean(const int scores[], size_t n)
//   int minimum(const int scores[], size_t n)
//   int maximum(const int scores[], size_t n)
//   void sort(int scores[], size_t n)
//       Sort ascending, in place. Write it yourself: insertion sort or
//       bubble sort is fine.
//   double median(int scores[], size_t n)
//       Sorts the array, then returns the middle value (or the average of
//       the two middle values when n is even).
//   void histogram(const int scores[], size_t n, int buckets[10])
//       buckets[0] counts scores 0-9, buckets[1] 10-19, ...,
//       buckets[9] counts 90-100 (100 goes in the last bucket).

// I AM NOT DONE

#include <stddef.h>

#include "clings.h"

// Write your functions here.

int main(void) {
    int scores[] = {72, 95, 61, 88, 100, 45, 77, 83, 90, 59};
    size_t n = sizeof(scores) / sizeof(scores[0]);

    CHECK_DBL(mean(scores, n), 77.0);
    CHECK_INT(minimum(scores, n), 45);
    CHECK_INT(maximum(scores, n), 100);

    int buckets[10] = {0};
    histogram(scores, n, buckets);
    CHECK_INT(buckets[4], 1);  // 45
    CHECK_INT(buckets[5], 1);  // 59
    CHECK_INT(buckets[7], 2);  // 72, 77
    CHECK_INT(buckets[8], 2);  // 88, 83
    CHECK_INT(buckets[9], 3);  // 95, 100, 90
    CHECK_INT(buckets[0], 0);

    CHECK_DBL(median(scores, n), 80.0);  // (77 + 83) / 2
    // median sorted the array:
    CHECK_INT(scores[0], 45);
    CHECK_INT(scores[9], 100);
    for (size_t i = 1; i < n; i++) {
        CHECK(scores[i - 1] <= scores[i]);
    }

    int odd[] = {5, 1, 3};
    CHECK_DBL(median(odd, 3), 3.0);

    return clings_report();
}
