#pragma once

#include "math.h"
#include <stdbool.h>

typedef struct Point {
    double x, y;
} Point;
Point newPt(double p, double q) { Point point ; point.x = p; point.y = q; return point;}
bool samePt(Point p1, Point p2) {if (p1.x == p2.x && p1.y == p2.y) return true; else return false;}
double mod(Point a, Point b) { return sqrt( pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); }
Point addPts(Point a, Point b) { return newPt(a.x + b.x, a.y + b.y);}
Point scalePt(Point a, double s) { return newPt(a.x * s, a.y * s);}

typedef struct Rect {
    double x,y,w,h;
} Rect ;
Rect newRect(double x, double y, double w, double h) {
    Rect rect;
    rect.x = x ; rect.y = y ; rect.w = w ; rect.h = h;
    return rect;
}
bool inRect(Point point, Rect rect) {
    return (point.x > (rect.x - rect.w) &&
            point.x <= (rect.x + rect.w) &&
            point.y > (rect.y - rect.h) &&
            point.y <= (rect.y + rect.h));
}
bool intersect(Rect rect1, Rect rect2) {
    int maxLeft  = fmax(rect1.x-rect1.w, rect2.x-rect2.w);
    int minRight = fmin(rect1.x+rect1.w, rect2.x+rect2.w);
    int maxDown  = fmax(rect1.y-rect1.h, rect2.y-rect2.h);
    int minUp    = fmin(rect1.y+rect1.h, rect2.y+rect2.h);

    if (maxLeft < minRight && maxDown<minUp) return true;

    return false;
}


typedef struct {
    Point pos;
    Point vel;
    Point acc;
} Particle;