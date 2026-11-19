// headers1.c - solution (the fix is in geometry.h)

#include "geometry.h"
#include "geometry.h"

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
