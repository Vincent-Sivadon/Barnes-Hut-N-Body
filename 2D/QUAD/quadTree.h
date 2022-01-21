#pragma once

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


#include "global.h"
#include "geometry.h"


// Structure principale de la méthode deBarnes-Hut
typedef struct Quad {
    // Limites spatiales
    Rect boundary;

    // Combien il contient de corps (en comptant ceux de ses descendants)
    int size;

    // Quel est l'id du corps qu'il contient (id=-1 si aucun)
    int id;

    // Indique si le quad est un noeud extérieur (contient un corps) ou intérieur (divisé)
    bool is_divided;

    // Descendants à allouer si le quad devient divisé
    struct Quad* northwest;
    struct Quad* northeast;
    struct Quad* southwest;
    struct Quad* southeast;
} Quad;

// Creation d'un nouveau quad
Quad* newQuad(Rect boundary) {
    // Allocation mémoire
    Quad* quad = malloc(sizeof(Quad));

    // Limites spatiales
    quad->boundary = boundary;
    
    // Un quad est par défaut extérieur sans corps
    quad->northwest = NULL;
    quad->northeast = NULL;
    quad->southwest = NULL;
    quad->southeast = NULL;

    
    quad->is_divided = false;  // quad extérieur (non divisé)
    quad->id         = -1;     // sans corps
    quad->size       = 0;

    return quad;
}


// Transforme un quad extérieur en quad divisé (c'est à dire qu'il contient des descendants)
void subdivide(Quad* quad) {
    // Get variables one time
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

    // Le quad est maintenant divisé
    quad->is_divided = true;
    quad->id         = -1; // et ne contient plus à proprement parlé de corps
}

// Attribue i à un noeud extérieur du quad (récursif)
void insertParticle(Quad* quad, int i) {
    // Extract coordinates
    double ix = pos.x[i];
    double iy = pos.y[i];

    // S'il n'est pas contenu dans les limites de ce quad, on sort
    if( !inRect(ix, iy, quad->boundary) ) return ;

    // 1 more body in that quad
    quad->size++;

    // If external
    if (!quad->is_divided) {
        // If empty
        if (quad->size == 1) {quad->id = i; return; }
        // If not
        else {
            // Keep temporary quad body
            int tmp = quad->id;

            // Subdivide
            subdivide(quad);

            // Re-insert body deeper
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

// Nettoyage de la mémoire alloué par tout l'arbre (quad)
void deconstructTree(Quad* quad) {
    if (quad->is_divided) {
        deconstructTree(quad->northwest);
        deconstructTree(quad->northeast);
        deconstructTree(quad->southwest);
        deconstructTree(quad->southeast);
    }
    free(quad);
}

// Dessine les limitations du quad (SDL)
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

/* Deprecated
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
*/