// macros2.c - solution

#include "clings.h"

#define VERSION_MAJOR 2
#define VERSION_MINOR 0
#define FEATURE_TURBO
#define STR(x) #x

const char *build_mode(void) {
#ifdef FEATURE_TURBO
    return "turbo";
#else
    return "normal";
#endif
}

int main(void) {
    CHECK_STR(build_mode(), "turbo");

#if VERSION_MAJOR >= 2
    const char *api = "new";
#else
    const char *api = "old";
#endif
    CHECK_STR(api, "new");

    CHECK_STR(STR(hello), "hello");
    CHECK_STR(STR(1 + 2), "1 + 2");

    return clings_report();
}
