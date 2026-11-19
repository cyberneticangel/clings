// project_xmacros.c - PROJECT: Macro toolbox
//
// Build a set of macros you'd find in many real C codebases.
//
//   MIN(a, b), MAX(a, b)       - the usual (parenthesize everything!)
//   CLAMP(x, lo, hi)           - x limited to the range [lo, hi]
//   SWAP(type, a, b)           - swaps two variables of the given type.
//                                Wrap multi-statement macros in
//                                do { ... } while (0) so they behave like a
//                                single statement (try it in an if/else!).
//   EXPECT_EQ(a, b)            - your own mini test macro: if a != b, it
//                                records a failure by calling
//                                record_failure(#a " == " #b, __LINE__)
//
// Then the star of the show: the "X macro" technique. Define the list of
// colors ONCE, and generate both the enum and a matching array of names
// from it, so they can never get out of sync:
//
//     #define COLOR_LIST(X) X(RED) X(GREEN) X(BLUE)
//
//     #define AS_ENUM(name) COLOR_##name,      // ## pastes tokens together
//     typedef enum { COLOR_LIST(AS_ENUM) COLOR_COUNT } Color;
//     // expands to: typedef enum { COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_COUNT } Color;
//
// Define AS_STRING and use it to build color_names[] = {"RED", ...}.
// Add YELLOW to the list: everything else should update automatically.

// I AM NOT DONE

#include "clings.h"

// --- failure log used by EXPECT_EQ ---
static const char *last_failure = "";
static int last_failure_line = 0;
static int failure_count = 0;

static void record_failure(const char *expr, int line) {
    last_failure = expr;
    last_failure_line = line;
    failure_count++;
}

// TODO: MIN, MAX, CLAMP, SWAP, EXPECT_EQ

#define COLOR_LIST(X) X(RED) X(GREEN) X(BLUE)

#define AS_ENUM(name) COLOR_##name,
typedef enum { COLOR_LIST(AS_ENUM) COLOR_COUNT } Color;

// TODO: AS_STRING and color_names

int main(void) {
    CHECK_INT(MIN(3, 7), 3);
    CHECK_INT(MAX(3, 7), 7);
    CHECK_INT(MIN(1 + 1, 3) * 10, 20);
    CHECK_INT(CLAMP(15, 0, 10), 10);
    CHECK_INT(CLAMP(-5, 0, 10), 0);
    CHECK_INT(CLAMP(5, 0, 10), 5);

    int a = 1, b = 2;
    if (a < b)
        SWAP(int, a, b);
    else
        a = 100;
    CHECK_INT(a, 2);
    CHECK_INT(b, 1);

    double x = 1.5, y = 2.5;
    SWAP(double, x, y);
    CHECK_DBL(x, 2.5);

    EXPECT_EQ(2 + 2, 4);
    CHECK_INT(failure_count, 0);
    int expect_line = __LINE__ + 1;
    EXPECT_EQ(2 + 2, 5);
    CHECK_INT(failure_count, 1);
    CHECK_STR(last_failure, "2 + 2 == 5");
    CHECK_INT(last_failure_line, expect_line);

    CHECK_INT(COLOR_COUNT, 4);
    CHECK_INT(COLOR_YELLOW, 3);
    CHECK_STR(color_names[COLOR_RED], "RED");
    CHECK_STR(color_names[COLOR_BLUE], "BLUE");
    CHECK_STR(color_names[COLOR_YELLOW], "YELLOW");

    return clings_report();
}
