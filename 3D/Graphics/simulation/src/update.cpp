#include "update.h"

#include "gtx/norm.hpp"

#include <iostream>
#include <math.h>


// Modify the acceleration of the body of index i according to the Octree structure
void compute_acceleration(Octree* octree, int i, glm::mat4* mM, glm::vec3* acc) {
    // Acceleration of our current body
    float ax = mM[i][3].x;
    float ay = mM[i][3].y;
    float az = mM[i][3].z;

    // If external (then it contains only one body)
    if( !octree->isDivided) {
        // if the 2 bodies are the same, stop computing
        if (octree->id == i || octree->size==0) return;

        // Compute the force between the current body and the one in this external node of the octree
        float bx = mM[octree->id][3].x;
        float by = mM[octree->id][3].y;
        float bz = mM[octree->id][3].z;

        // distance between the two
        double r = sqrt( (ax - bx)*(ax - bx) + (ay - by)*(ay - by) + (az-bz)*(az-bz));

        // new acceleration of our current body
        acc[i].x += (bx - ax) * 5 / (1e7 + r*r*r);
        acc[i].y += (by - ay) * 5 / (1e7 + r*r*r);
        acc[i].z += (bz - az) * 5 / (1e7 + r*r*r);

    } else {  // if divided 
        // Distance between octree center and our body i
        double r2 = (octree->box.x - ax)*(octree->box.x - ax) +
                    (octree->box.y - ay)*(octree->box.y - ay) +
                    (octree->box.z - az)*(octree->box.z - az);

        // Solid angle that represent how little the box is from our body i
        double theta = (octree->box.w*octree->box.h) / r2;

        // if the octree is far enough, than we take all of the bodies he contains (including his children)
        // as if they were only one body with all there masses and at the center of the octree
        if(theta < 0.5) {
            // octree center position
            float bx = octree->box.x;
            float by = octree->box.y;
            float bz = octree->box.z;

            // distance separating the body and the octree center
            double r = sqrt( r2 );

            // body i acceleration update
            acc[i].x += (bx - ax) * 5 * octree->size / (1e7 + r*r*r);
            acc[i].y += (by - ay) * 5 * octree->size / (1e7 + r*r*r);
            acc[i].z += (bz - az) * 5 * octree->size / (1e7 + r*r*r);

            // don't go deeper in the tree
            return;
        }
        
        // If the octree isn't far enough, than we can't approximate, and we have to go deeper
        for(u64 p=0 ; p<2; p++)
            for(u64 q=0 ; q<2; q++)
                for(u64 k=0 ; k<2; k++)
                    compute_acceleration(octree->subtrees[p][q][k], i, mM, acc);
    }
    
}

// intermediate function that indicate if two bodies collides
bool intersect(int i, int j, glm::mat4* mM) {
    float xi = mM[i][3].x; float xj = mM[j][3].x;
    float yi = mM[i][3].y; float yj = mM[j][3].y;
    float zi = mM[i][3].z; float zj = mM[j][3].z;
    
    float cubeSize = 0.05;
    float xMax, xMin, yMax, yMin, zMax, zMin;
    if(xi >= xj) {xMax = xi ; xMin = xj;}
    else {xMax = xj ; xMin = xi ;}
    if(yi >= yj) {yMax = yi ; yMin = yj;}
    else {yMax = yj ; yMin = yi ;}
    if(zi >= zj) {zMax = zi ; zMin = zj;}
    else {zMax = zj ; zMin = zi ;}

    bool intersectx = (xMax - cubeSize) <= (xMin + cubeSize) ;
    bool intersecty = (yMax - cubeSize) <= (yMin + cubeSize) ;
    bool intersectz = (zMax - cubeSize) <= (zMin + cubeSize) ;

    if (intersectx && intersecty && intersectz) return true;

    return false;
}

// swap velocities if a collision occured
void resolve_collisions(int i, int j, glm::vec3* vel, glm::mat4* mM) {    
    // si les cubes ne s'interceptent pas
    if ( !intersect(i,j,mM) ) return ;

    // sinon :
    double tmp_vx = vel[i].x;
    double tmp_vy = vel[i].y;
    double tmp_vz = vel[i].z;

    vel[i].x = vel[j].x  ;  vel[i].y = vel[j].y ; vel[i].z = vel[j].z;
    vel[j].x = tmp_vx    ;  vel[j].y = tmp_vy   ; vel[j].z = tmp_vz;
}

// only search collision if bodies are close enough
void search_potential_collisions(Octree* octree, int i, Box range, glm::vec3* vel, glm::mat4* mM) {
    if( !octree->box.intersect(range) ) return;

    if (!octree->isDivided) resolve_collisions(i, octree->id, vel, mM);
    else {
        for(int p=0 ; p<2; p++)
            for(int q=0 ; q<2; q++)
                for(int k=0 ; k<2; k++)
                    search_potential_collisions(octree->subtrees[p][q][k], i, range, vel, mM);
    }
}


// Update bodies positions
void update(glm::mat4* mM, glm::vec3* vel, glm::vec3* acc, u64 N, Box box)
{
    // Time step simulation
    float dt = 0.1;

    // Create newOctree
    Octree* octree = new Octree(box);

    octree->subdivide();
    
    // Insert all particles
    for(u64 i=0; i<N ; i++)
        octree->insert(i,mM);



    for(u64 i=0 ; i<N ; i++)
    {
        // reset i's acceleration
        acc[i].x = 0;
        acc[i].y = 0;
        acc[i].z = 0;

        // update i's acceleration
        compute_acceleration(octree, i, mM, acc);

        vel[i].x += (acc[i].x * dt);
        vel[i].y += (acc[i].y * dt);
        vel[i].z += (acc[i].z * dt);   


        // Update i's position
        mM[i][3].x += (vel[i].x * dt);
        mM[i][3].y += (vel[i].y * dt);
        mM[i][3].z += (vel[i].z * dt);
    }

/*
    for(u64 i=0; i<N ; i++)
    {
        Box range(mM[i][3].x, mM[i][3].y, mM[i][3].z, 2, 2, 2);
        search_potential_collisions(octree, i, range, vel, mM) ;
    }
*/

    // destroy the octree structure
    octree->destroy();

}



// "naive" version
void updateV0(glm::mat4* modelMatrices, glm::vec3* velocities, unsigned int N)
{
    // Time step simulation
    float dt = 0.01;


    for(unsigned int i=0 ; i<N ; i++)
    {
        // Force que subira i
        float fx = 0.0;
        float fy = 0.0;
        float fz = 0.0;

        // Position de i
        float xi = modelMatrices[i][3].x;
        float yi = modelMatrices[i][3].y;
        float zi = modelMatrices[i][3].z;

        for(unsigned j=0 ; j<N ; j++)
        {
            // Position de j
            float xj = modelMatrices[j][3].x;
            float yj = modelMatrices[j][3].y;
            float zj = modelMatrices[j][3].z;

            // Vecteur position components
            float dx = xj - xi;
            float dy = yj - yi;
            float dz = zj - zi;
            
            float d = sqrt(
                (dx * dx) + (dy * dy) + (dz * dz) + 1e-20
            );

            float d3inv = 1/(d*d*d);

            fx += dx * d3inv;
            fy += dy * d3inv;
            fz += fz * d3inv;
        }

        // Force vector (we already multiply by dt)
        glm::vec3 force(dt*fx,dt*fy,dt*fz);

        // Update velocity
        velocities[i] += force;

        // Update position
        modelMatrices[i][3].x += (velocities[i].x * dt);
        modelMatrices[i][3].y += (velocities[i].y * dt);
        modelMatrices[i][3].z += (velocities[i].z * dt);
    }

}