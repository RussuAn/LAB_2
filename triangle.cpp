#include "triangle.h"

double cross_product(const Point &p1, const Point &p2, const Point &p3) {
    return ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}

double Triangle::area() const {
    return 0.5 * fabs((A.x * B.y - B.x * A.y) + (B.x * C.y - C.x * B.y) + (C.x * A.y - A.x * C.y));
}

bool Triangle::contains(const Point &P) const {
    double CP1 = cross_product(A, B, P);
    double CP2 = cross_product(B, C, P);
    double CP3 = cross_product(C, A, P);

    return(CP1 >= 0 && CP2 >= 0 && CP3 >= 0) || (CP1 <= 0 && CP2 <= 0 && CP3 <= 0);
}

bool Triangle::degenerate() const {
    return area() < 1e-9;
}

bool Triangle::on_border(const Point &P) const {
    return fabs(cross_product(A, B, P)) < 1e-9 &&
    (min(A.x, B.x) <= P.x && P.x <= max(A.x, B.x)) &&
    (min(A.y, B.y) <= P.y && P.y <= max(A.y, B.y)) ||
    fabs(cross_product(B, C, P)) < 1e-9 &&
    (min(B.x, C.x) <= P.x && P.x <= max(B.x, C.x)) &&
    (min(B.y, C.y) <= P.y && P.y <= max(B.y, B.y)) ||
    fabs(cross_product(C, A, P)) < 1e-9 &&
    (min(C.x, A.x) <= P.x && P.x <= max(C.x, A.x)) &&
    (min(C.y, A.y) <= P.y && P.y <= max(C.y, A.y));
}
