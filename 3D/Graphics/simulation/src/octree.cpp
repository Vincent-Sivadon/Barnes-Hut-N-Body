#include "octree.h"

#include <iostream>


void Octree::subdivide() {
    // Get variables
    float x = box.x;
    float y = box.y;
    float z = box.z;
    float w = box.w;
    float h = box.h;
    float d = box.d;

    for(long long int i=0 ; i<2; i++)
        for(long long int j=0 ; j<2; j++)
            for(long long int k=0 ; k<2; k++)
                subtrees[i][j][k] = new Octree(Box(
                    x-w/2 + i*w,
                    y-h/2 + j*h,
                    z-d/2 + k*d,
                    w/2,
                    h/2,
                    d/2));
    isDivided = true;
    id = -1;
}



void Octree::insert(u64 i, glm::mat4 * mM) {
    float ax = mM[i][3].x;
    float ay = mM[i][3].y;
    float az = mM[i][3].z;

    if ( !box.inBox(ax, ay, az)) return ;

    // 1 more point in that octree
    size++;
    

    // If external
    if( !isDivided ) {
        // If empty
        if( size == 1 ) {id = i ; return; }
        // If no
        else {
            // Keep temporary octree particle
            u64 tmp = id;

            // Subdivide
            subdivide();

            // Re-inset point deeper
            insert(tmp, mM);
            size -= 2;
            insert(i, mM);
        }
    } else {
        for(u64 p=0 ; p<2; p++)
            for(u64 q=0 ; q<2; q++)
                for(u64 k=0 ; k<2; k++)
                    subtrees[p][q][k]->insert(i, mM);
    }
}


void Octree::destroy() {
    if (isDivided) {
        for(u64 i=0 ; i<2; i++)
            for(u64 j=0 ; j<2; j++)
                for(u64 k=0 ; k<2; k++)
                    subtrees[i][j][k]->destroy();
    }
    delete this;
}