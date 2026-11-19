/*
 * clings.h - tiny test helpers used by every exercise.
 *
 * You don't need to edit this file, but feel free to read it!
 * Everything here is plain C you will understand by the end of the course.
 */
#ifndef CLINGS_H
#define CLINGS_H

#include <math.h>
#include <stdio.h>
#include <string.h>

static int clings_checks __attribute__((unused)) = 0;
static int clings_failures __attribute__((unused)) = 0;

#define CLINGS_RED   "\033[31m"
#define CLINGS_GREEN "\033[32m"
#define CLINGS_RESET "\033[0m"

#define CLINGS_FAIL_HEADER()                                                  \
    fprintf(stderr, CLINGS_RED "  x " CLINGS_RESET "%s:%d: ", __FILE__,       \
            __LINE__)

/* CHECK(condition) - passes when condition is true (non-zero). */
#define CHECK(cond)                                                           \
    do {                                                                      \
        clings_checks++;                                                      \
        if (!(cond)) {                                                        \
            clings_failures++;                                                \
            CLINGS_FAIL_HEADER();                                             \
            fprintf(stderr, "CHECK(%s) failed\n", #cond);                     \
        }                                                                     \
    } while (0)

/* CHECK_INT(actual, expected) - compares two integers. */
#define CHECK_INT(actual, expected)                                           \
    do {                                                                      \
        long long clings_a_ = (long long)(actual);                            \
        long long clings_e_ = (long long)(expected);                          \
        clings_checks++;                                                      \
        if (clings_a_ != clings_e_) {                                         \
            clings_failures++;                                                \
            CLINGS_FAIL_HEADER();                                             \
            fprintf(stderr, "%s\n      expected: %lld\n      got:      %lld\n", \
                    #actual, clings_e_, clings_a_);                           \
        }                                                                     \
    } while (0)

/* CHECK_DBL(actual, expected) - compares two floating point numbers. */
#define CHECK_DBL(actual, expected)                                           \
    do {                                                                      \
        double clings_a_ = (double)(actual);                                  \
        double clings_e_ = (double)(expected);                                \
        clings_checks++;                                                      \
        if (fabs(clings_a_ - clings_e_) > 1e-6) {                             \
            clings_failures++;                                                \
            CLINGS_FAIL_HEADER();                                             \
            fprintf(stderr, "%s\n      expected: %g\n      got:      %g\n",   \
                    #actual, clings_e_, clings_a_);                           \
        }                                                                     \
    } while (0)

/* CHECK_STR(actual, expected) - compares two C strings. */
#define CHECK_STR(actual, expected)                                           \
    do {                                                                      \
        const char *clings_a_ = (actual);                                     \
        const char *clings_e_ = (expected);                                   \
        clings_checks++;                                                      \
        if (clings_a_ == NULL || clings_e_ == NULL ||                         \
            strcmp(clings_a_, clings_e_) != 0) {                              \
            clings_failures++;                                                \
            CLINGS_FAIL_HEADER();                                             \
            fprintf(stderr,                                                   \
                    "%s\n      expected: \"%s\"\n      got:      \"%s\"\n",   \
                    #actual, clings_e_ ? clings_e_ : "(null)",                \
                    clings_a_ ? clings_a_ : "(null)");                        \
        }                                                                     \
    } while (0)

/* Call this at the end of main: `return clings_report();` */
static inline int clings_report(void) {
    if (clings_failures > 0) {
        fprintf(stderr, CLINGS_RED "  %d of %d checks failed" CLINGS_RESET "\n",
                clings_failures, clings_checks);
        return 1;
    }
    printf(CLINGS_GREEN "  all %d checks passed" CLINGS_RESET "\n",
           clings_checks);
    return 0;
}

#endif /* CLINGS_H */
