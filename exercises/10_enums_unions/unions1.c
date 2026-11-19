// unions1.c
//
// A union is like a struct, except all members share the SAME memory. It's
// only as big as its largest member, and only one member is meaningful at a
// time.
//
// Unions are usually combined with an enum "tag" that records which member
// is currently in use. This is called a *tagged union*, and it's how you
// build a value that can be one of several different kinds.
//
// Implement `shape_area` and the two constructor functions.

// I AM NOT DONE

#include "clings.h"

#define PI 3.14159265358979

typedef enum { SHAPE_CIRCLE, SHAPE_RECT } ShapeKind;

typedef struct {
    ShapeKind kind;
    union {
        struct { double radius; } circle;
        struct { double width, height; } rect;
    };
} Shape;

Shape make_circle(double radius) {
    Shape s;
    s.kind = SHAPE_CIRCLE;
    // TODO
    return s;
}

Shape make_rect(double width, double height) {
    // TODO
}

double shape_area(Shape s) {
    // TODO: switch on s.kind
}

int main(void) {
    Shape c = make_circle(2.0);
    Shape r = make_rect(3.0, 5.0);

    CHECK_INT(c.kind, SHAPE_CIRCLE);
    CHECK_INT(r.kind, SHAPE_RECT);
    CHECK_DBL(c.circle.radius, 2.0);

    CHECK_DBL(shape_area(c), PI * 4.0);
    CHECK_DBL(shape_area(r), 15.0);

    // The union is the size of its biggest member, not the sum.
    CHECK(sizeof(Shape) < sizeof(ShapeKind) + 3 * sizeof(double));

    return clings_report();
}
