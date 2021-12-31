#pragma once

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


#include "global.h"
#include "geometry.h"


typedef struct Octree {
    Box boundary;
    int size;
    int id;
    bool is_divided;

    struct Octree* subtrees[2][2][2];
} Octree;

Octree* newOctree(Box boundary) {
    Octree* octree = malloc(sizeof(Octree));
    octree->boundary = boundary;
    
    for(int i=0 ; i<2; i++)
        for(int j=0 ; j<2; j++)
            for(int k=0 ; k<2; k++)
                octree->subtrees[i][j][k] = NULL;

    octree->is_divided = false;
    octree->id         = -1;
    octree->size       = 0;

    return octree;
}



void subdivide(Octree* octree) {
    // Get variables
    double x = octree->boundary.x;
    double y = octree->boundary.y;
    double z = octree->boundary.z;
    double w = octree->boundary.w;
    double h = octree->boundary.h;
    double d = octree->boundary.d;

    for(int i=0 ; i<2; i++)
        for(int j=0 ; j<2; j++)
            for(int k=0 ; k<2; k++)
                octree->subtrees[i][j][k] = newOctree(newBox(x+(i-1)*w/2, y+(j-1)*h/2, z+(k-1)*d/2, w/2, h/2, d/2));

    octree->is_divided = true;
    octree->id         = -1;
}


void insertParticle(Octree* octree, int i) {
    // If point not in box
    Point a = {pos.x[i],pos.y[i], pos.z[i]};
    if( !inBox(a, octree->boundary) ) return ;

    // 1 more point in that octree
    octree->size++;

    // If external
    if (!octree->is_divided) {
        // If empty
        if (octree->size == 1) {octree->id = i; return; }
        // If not
        else {
            // Keep temporary octree particle
            int tmp = octree->id;

            // Subdivide
            subdivide(octree);

            // Re-insert point deeper
            insertParticle(octree, tmp);
            octree->size -= 2;
            insertParticle(octree, i);
        }
    // If internal (is_divided)
    } else {
        for(int p=0 ; p<2; p++)
            for(int q=0 ; q<2; q++)
                for(int k=0 ; k<2; k++)
                    insertParticle(octree->subtrees[p][q][k], i);
    }
}


void deconstructTree(Octree* octree) {
    if (octree->is_divided) {
        for(int i=0 ; i<2; i++)
            for(int j=0 ; j<2; j++)
                for(int k=0 ; k<2; k++)
                    free(octree->subtrees[i][j][k]);
    }
    free(octree);
}
