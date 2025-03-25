#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;
    double area() const;
    bool contains(const Point &P) const;
    bool degenerate() const;
    bool on_border(const Point &P) const;
};

double cross_product(const Point &p1, const Point &p2, const Point &p3);

#endif