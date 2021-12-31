#pragma once

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


#include "global.h"
#include "geometry.h"


typedef struct Quad {
    Rect boundary;
    int size;
    int id;
    bool is_divided;

    struct Quad* northwest;
    struct Quad* northeast;
    struct Quad* southwest;
    struct Quad* southeast;

} Quad;

Quad* newQuad(Rect boundary) {
    Quad* quad = malloc(sizeof(Quad));
    quad->boundary = boundary;
    
    quad->northwest = NULL;
    quad->northeast = NULL;
    quad->southwest = NULL;
    quad->southeast = NULL;

    quad->is_divided = false;
    quad->id         = -1;
    quad->size       = 0;

    return quad;
}



void subdivide(Quad* quad) {
    // Get variables
    double x = quad->boundary.x;
    double y = quad->boundary.y;
    double w = quad->boundary.w;
    double h = quad->boundary.h;

    // Create Rectangles corresponding to subquads
    Rect ne = newRect(x + w/2, y-h/2, w/2, h/2);
    Rect se = newRect(x + w/2, y+h/2, w/2, h/2);
    Rect nw = newRect(x - w/2, y-h/2, w/2, h/2);
    Rect sw = newRect(x - w/2, y+h/2, w/2, h/2);

    // Create Subquad trees
    quad->northwest = newQuad(nw);
    quad->northeast = newQuad(ne);
    quad->southwest = newQuad(sw);
    quad->southeast = newQuad(se);

    quad->is_divided = true;
    quad->id         = -1;
}


void insertParticle(Quad* quad, int i) {
    // If point not in rect
    Point a = {pos.x[i],pos.y[i]};
    if( !inRect(a, quad->boundary) ) return ;

    // 1 more point in that quad
    quad->size++;

    // If external
    if (!quad->is_divided) {
        // If empty
        if (quad->size == 1) {quad->id = i; return; }
        // If not
        else {
            // Keep temporary quad particle
            int tmp = quad->id;

            // Subdivide
            subdivide(quad);

            // Re-insert point deeper
            insertParticle(quad, tmp);
            quad->size -= 2;
            insertParticle(quad, i);
        }
    // If internal (is_divided)
    } else {
        insertParticle(quad->northwest, i);
        insertParticle(quad->northeast, i);
        insertParticle(quad->southwest, i);
        insertParticle(quad->southeast, i);
    }
}


void deconstructTree(Quad* quad) {
    if (quad->is_divided) {
        deconstructTree(quad->northwest);
        deconstructTree(quad->northeast);
        deconstructTree(quad->southwest);
        deconstructTree(quad->southeast);
    }
    free(quad);
}

#if defined SDL
void drawQuad(SDL_Renderer* renderer, Quad* quad) {
    // If external
    if( !quad->is_divided ) return;

    // If internal
    else {
        Rect bounds = quad->boundary;
        if (quad->id == -1)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        else if (quad->id == 0)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (quad->id == 1)
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        else if (quad->id == 2)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else if (quad->id == 3)
            SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
        else if (quad->id == 4)
            SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);


        SDL_RenderDrawLine(renderer, bounds.x - bounds.w, bounds.y,
                                    bounds.x + bounds.w, bounds.y);
        SDL_RenderDrawLine(renderer, bounds.x, bounds.y - bounds.h,
                                    bounds.x, bounds.y + bounds.h);
        drawQuad(renderer, quad->northwest);
        drawQuad(renderer, quad->northeast);
        drawQuad(renderer, quad->southwest);
        drawQuad(renderer, quad->southeast);
    }
}
#endif

Point centerOfMass(Quad* quad) {
    Point cm = {0,0};
    if (!quad->is_divided) {
        if (quad->size==0) return cm;
        Point id = {pos.x[quad->id], pos.y[quad->id]};
        return id;
    }

    cm = addPts(cm, centerOfMass(quad->northwest));
    cm = addPts(cm, centerOfMass(quad->northeast));
    cm = addPts(cm, centerOfMass(quad->southwest));
    cm = addPts(cm, centerOfMass(quad->southeast));

    return cm;
}

