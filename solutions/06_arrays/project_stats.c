// project_stats.c - solution

#include <stddef.h>

#include "clings.h"

double mean(const int scores[], size_t n) {
    long sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += scores[i];
    }
    return (double)sum / n;
}

int minimum(const int scores[], size_t n) {
    int min = scores[0];
    for (size_t i = 1; i < n; i++) {
        if (scores[i] < min) {
            min = scores[i];
        }
    }
    return min;
}

int maximum(const int scores[], size_t n) {
    int max = scores[0];
    for (size_t i = 1; i < n; i++) {
        if (scores[i] > max) {
            max = scores[i];
        }
    }
    return max;
}

// Insertion sort: grow a sorted prefix one element at a time.
void sort(int scores[], size_t n) {
    for (size_t i = 1; i < n; i++) {
        int key = scores[i];
        size_t j = i;
        while (j > 0 && scores[j - 1] > key) {
            scores[j] = scores[j - 1];
            j--;
        }
        scores[j] = key;
    }
}

double median(int scores[], size_t n) {
    sort(scores, n);
    if (n % 2 == 1) {
        return scores[n / 2];
    }
    return (scores[n / 2 - 1] + scores[n / 2]) / 2.0;
}

void histogram(const int scores[], size_t n, int buckets[10]) {
    for (size_t i = 0; i < n; i++) {
        int b = scores[i] / 10;
        if (b > 9) {
            b = 9;
        }
        buckets[b]++;
    }
}

int main(void) {
    int scores[] = {72, 95, 61, 88, 100, 45, 77, 83, 90, 59};
    size_t n = sizeof(scores) / sizeof(scores[0]);

    CHECK_DBL(mean(scores, n), 77.0);
    CHECK_INT(minimum(scores, n), 45);
    CHECK_INT(maximum(scores, n), 100);

    int buckets[10] = {0};
    histogram(scores, n, buckets);
    CHECK_INT(buckets[4], 1);
    CHECK_INT(buckets[5], 1);
    CHECK_INT(buckets[7], 2);
    CHECK_INT(buckets[8], 2);
    CHECK_INT(buckets[9], 3);
    CHECK_INT(buckets[0], 0);

    CHECK_DBL(median(scores, n), 80.0);
    CHECK_INT(scores[0], 45);
    CHECK_INT(scores[9], 100);
    for (size_t i = 1; i < n; i++) {
        CHECK(scores[i - 1] <= scores[i]);
    }

    int odd[] = {5, 1, 3};
    CHECK_DBL(median(odd, 3), 3.0);

    return clings_report();
}
