#pragma once

#include "math.h"
#include <stdbool.h>


// Structure représentant les limites spatiales d'un quad
// x et y représentent le centre
// w et h représentent la demie largeur et demie hauteur
typedef struct Rect {
    double x,y,w,h;
} Rect ;

// Creation d'un nouveau rectangle
Rect newRect(double x, double y, double w, double h) {
    Rect rect;
    rect.x = x ; rect.y = y ; rect.w = w ; rect.h = h;
    return rect;
}

// Indique si un coprs est dans le rectangle rect
// x et y les coordonnées du corps
bool inRect(double x, double y, Rect rect) {
    return (x >  (rect.x - rect.w) &&
            x <= (rect.x + rect.w) &&
            y >  (rect.y - rect.h) &&
            y <= (rect.y + rect.h));
}

// indique si deux rectangles rect1 et rect2 se chevauchent
bool intersect(Rect rect1, Rect rect2) {
    int maxLeft  = fmax(rect1.x-rect1.w, rect2.x-rect2.w);
    int minRight = fmin(rect1.x+rect1.w, rect2.x+rect2.w);
    int maxDown  = fmax(rect1.y-rect1.h, rect2.y-rect2.h);
    int minUp    = fmin(rect1.y+rect1.h, rect2.y+rect2.h);

    if (maxLeft < minRight && maxDown<minUp) return true;

    return false;
}

// Structure qui permettra la manipulation de l'ensemble
// des positions et des vitesses.
// Contient tableau à allouer
typedef struct {
    double* x;
    double* y;
} Field;