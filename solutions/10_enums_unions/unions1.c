// unions1.c - solution

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
    s.circle.radius = radius;
    return s;
}

Shape make_rect(double width, double height) {
    Shape s;
    s.kind = SHAPE_RECT;
    s.rect.width = width;
    s.rect.height = height;
    return s;
}

double shape_area(Shape s) {
    switch (s.kind) {
    case SHAPE_CIRCLE:
        return PI * s.circle.radius * s.circle.radius;
    case SHAPE_RECT:
        return s.rect.width * s.rect.height;
    }
    return 0.0;
}

int main(void) {
    Shape c = make_circle(2.0);
    Shape r = make_rect(3.0, 5.0);

    CHECK_INT(c.kind, SHAPE_CIRCLE);
    CHECK_INT(r.kind, SHAPE_RECT);
    CHECK_DBL(c.circle.radius, 2.0);

    CHECK_DBL(shape_area(c), PI * 4.0);
    CHECK_DBL(shape_area(r), 15.0);

    CHECK(sizeof(Shape) < sizeof(ShapeKind) + 3 * sizeof(double));

    return clings_report();
}
