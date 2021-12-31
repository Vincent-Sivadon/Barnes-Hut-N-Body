#pragma once

#include "math.h"
#include <stdbool.h>

typedef struct Point {
    double x, y, z;
} Point;
Point newPt(double p, double q, double r) { Point point ; point.x = p; point.y = q; point.z = r ; return point;}
bool samePt(Point p1, Point p2) {if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z) return true; else return false;}
double mod(Point a, Point b) { return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z)); }
Point addPts(Point a, Point b) { return newPt(a.x + b.x, a.y + b.y, a.z + b.z);}
Point scalePt(Point a, double s) { return newPt(a.x * s, a.y * s, a.z * s);}

typedef struct Box {
    double x,y,z;
    double w,h,d;
} Box ;
Box newBox(double x, double y, double z, double w, double h, double d) {
    Box box;
    box.x = x ; box.y = y ; box.z = z;
    box.w = w ; box.h = h ; box.d = d;
    return box;
}
bool inBox(Point point, Box box) {
    return (point.x > (box.x - box.w) &&
            point.x <= (box.x + box.w) &&
            point.y > (box.y - box.h) &&
            point.y <= (box.y + box.h) &&
            point.z > (box.z - box.d) &&
            point.z <= (box.z + box.d));
}
bool intersect(Box box1, Box box2) {
    Box maxX, minX, maxY, minY, maxZ, minZ;
    if (box1.x >= box2.x) {maxX = box1 ; minX = box2;}
    else {maxX = box2 ; minX = box1;}
    if (box1.y >= box2.y) {maxY = box1 ; minY = box2;}
    else {maxY = box2 ; minY = box1;}
    if (box1.z >= box2.z) {maxZ = box1 ; minZ = box2;}
    else {maxZ = box2 ; minZ = box1;}

    bool intersectx = (maxX.x - maxX.w) - (minX.x + minX.w) <= 0;
    bool intersecty = (maxY.y - maxY.h) - (minY.y + minY.h) <= 0;
    bool intersectz = (maxZ.z - maxZ.d) - (minZ.z + minZ.d) <= 0;


    if (intersectx && intersecty && intersectz) return true;

    return false;
}


typedef struct {
    double* x;
    double* y;
    double* z;
} Field;