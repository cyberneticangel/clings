// headers1.c
//
// `#include "file.h"` literally pastes the contents of file.h in place.
// In real projects, headers often get included more than once (directly, or
// indirectly through other headers). If a header defines a struct, pasting
// it twice is a "redefinition" error.
//
// The standard fix is an *include guard* at the top and bottom of every
// header:
//
//     #ifndef MY_HEADER_H
//     #define MY_HEADER_H
//     ... contents ...
//     #endif
//
// The first time, MY_HEADER_H isn't defined, so the contents are included and
// the macro gets defined. The second time, everything is skipped.
//
// Don't edit this file. Fix geometry.h (in the same folder).

// I AM NOT DONE

#include "geometry.h"
#include "geometry.h" // imagine this came in via some other header

#include "clings.h"

int main(void) {
    Vec2 a = {1.0, 2.0};
    Vec2 b = {3.0, 4.0};
    Vec2 c = vec2_add(a, b);

    CHECK_DBL(c.x, 4.0);
    CHECK_DBL(c.y, 6.0);
    CHECK_DBL(vec2_dot(a, b), 11.0);

    return clings_report();
}
