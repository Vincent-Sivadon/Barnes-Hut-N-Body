#include "octree.h"

#include <iostream>

// Initialise les enfants de cet octree
void Octree::subdivide() {
    // Get space limitations
    float x = box.x;
    float y = box.y;
    float z = box.z;
    float w = box.w;
    float h = box.h;
    float d = box.d;

    // Allocate every subtree with according space limitations
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
    // This octree is now Divided
    isDivided = true;

    // Indicates that it is no longer an external tree that contains a body
    id = -1;
}


// Insert the body of index i inside the octree structure
void Octree::insert(u64 i, glm::mat4 * mM) {
    // Coordinates of the body
    float ax = mM[i][3].x;
    float ay = mM[i][3].y;
    float az = mM[i][3].z;

    // If it is not in this octree's region, return
    if ( !box.inBox(ax, ay, az)) return ;

    // 1 more body in that octree or it's children
    size++;
    

    // If external (then it contains only one body)
    if( !isDivided ) {
        // If empty (size==1 cause we juste added by default size++)
        if( size == 1 ) {id = i ; return; } // we placed the body here and got out
        // If there is already a body
        else {
            // Keep it's id (we will delete it by subdividing the octree)
            u64 tmp = id;

            // Subdivide the octree
            subdivide();

            // Re-inset point deeper
            insert(tmp, mM);
            size -= 2;
            insert(i, mM);
        }
    } else {  // if divided, then insert deeper
        for(u64 p=0 ; p<2; p++)
            for(u64 q=0 ; q<2; q++)
                for(u64 k=0 ; k<2; k++)
                    subtrees[p][q][k]->insert(i, mM);
    }
}

// supprime l'espace mémoire allouée par cet octree et ses enfants
void Octree::destroy() {
    // If divided, then go deeper to delete all subtrees
    if (isDivided) {
        for(u64 i=0 ; i<2; i++)
            for(u64 j=0 ; j<2; j++)
                for(u64 k=0 ; k<2; k++)
                    subtrees[i][j][k]->destroy();
    }
    // once all of the octree's children have been destroyed, destroy it
    delete this;
}