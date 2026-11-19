// macros2.c
//
// More preprocessor tricks:
//
//   Conditional compilation: code between #if / #ifdef and #endif is only
//   compiled if the condition holds. Great for debug-only code or
//   platform-specific code.
//
//       #ifdef DEBUG
//           log_everything();
//       #endif
//
//   Stringification: inside a macro, #x turns the argument into a string
//   literal: STR(hello) -> "hello"
//
//   Predefined macros: __FILE__, __LINE__, __func__ (that last one is
//   technically a variable), handy for error messages.
//
// Make the checks pass by editing ONLY the #define lines.

// I AM NOT DONE

#include "clings.h"

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
// TODO: define FEATURE_TURBO
#define STR(x) x

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
