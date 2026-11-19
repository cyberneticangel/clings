// project_xmacros.c - solution

#include "clings.h"

static const char *last_failure = "";
static int last_failure_line = 0;
static int failure_count = 0;

static void record_failure(const char *expr, int line) {
    last_failure = expr;
    last_failure_line = line;
    failure_count++;
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(x, lo, hi) MIN(MAX((x), (lo)), (hi))

#define SWAP(type, a, b)   \
    do {                   \
        type swap_tmp_ = (a); \
        (a) = (b);         \
        (b) = swap_tmp_;   \
    } while (0)

#define EXPECT_EQ(a, b)                              \
    do {                                             \
        if ((a) != (b)) {                            \
            record_failure(#a " == " #b, __LINE__);  \
        }                                            \
    } while (0)

#define COLOR_LIST(X) X(RED) X(GREEN) X(BLUE) X(YELLOW)

#define AS_ENUM(name) COLOR_##name,
typedef enum { COLOR_LIST(AS_ENUM) COLOR_COUNT } Color;

#define AS_STRING(name) #name,
static const char *color_names[] = {COLOR_LIST(AS_STRING)};

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
