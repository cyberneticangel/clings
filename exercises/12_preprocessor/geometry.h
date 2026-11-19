// geometry.h - used by headers1.c
//
// Add an include guard to this header.
//
// (Usually a header would only contain declarations, and the function
// bodies would live in a separate geometry.c file. `static inline`
// functions are a common exception for tiny helpers.)

typedef struct {
    double x;
    double y;
} Vec2;

static inline Vec2 vec2_add(Vec2 a, Vec2 b) {
    Vec2 r = {a.x + b.x, a.y + b.y};
    return r;
}

static inline double vec2_dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}
