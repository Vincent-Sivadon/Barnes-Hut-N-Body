#pragma once

#include "math.h"
#include <stdbool.h>

#include <iostream>

struct Box {
    float x,y,z;
    float w,h,d;

    Box() {}
    Box(float X, float Y, float Z, float W, float H, float D)
        : x(X), y(Y), z(Z), w(W), h(H), d(D) {}

    bool inBox(float p, float q, float r) {
        return (p >  (x - w) &&
                p <= (x + w) &&
                q >  (y - h) &&
                q <= (y + h) &&
                r >  (z - d) &&
                r <= (z + d));
    }
    bool intersect(Box box) {
        float xMax, xMin, yMax, yMin, zMax, zMin;
        if(box.x >= x) {xMax = box.x ; xMin = x;}
        else {xMax = x ; xMin = box.x ;}
        if(box.y >= y) {yMax = box.y ; yMin = y;}
        else {yMax = y ; yMin = box.y ;}
        if(box.z >= z) {zMax = box.z ; zMin = z;}
        else {zMax = z ; zMin = box.z ;}

        bool intersectx = (xMax - w) <= (xMin + w) ;
        bool intersecty = (yMax - h) <= (yMin + h) ;
        bool intersectz = (zMax - d) <= (zMin + d) ;

        if (intersectx && intersecty && intersectz) return true;

        return false;
    }
};