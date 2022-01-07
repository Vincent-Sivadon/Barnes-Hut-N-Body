#pragma once

#include "octree.h"
#include "global.h"


//
void init_system(int n) {

    // Number of bodies
    N = n;
    Nt = 10;
    masse = 5;

    // Pointer to all particles
    pos.x = malloc(N * sizeof(double));
    pos.y = malloc(N * sizeof(double));
    pos.z = malloc(N * sizeof(double));
    vel.x = malloc(N * sizeof(double));
    vel.y = malloc(N * sizeof(double));
    vel.z = malloc(N * sizeof(double));
    acc.x = malloc(N * sizeof(double));
    acc.y = malloc(N * sizeof(double));
    acc.z = malloc(N * sizeof(double));


    // for every particles
    for(int i=0; i<N ; i++) {
        int r1 = rand(); int r2 = rand();
        float sign = (r1 > r2) ? 1 : -1;
        pos.x[i] = sign * (double)rand() / (double)RAND_MAX;
        pos.y[i] = (double)rand() / (double)RAND_MAX;
        pos.z[i] = sign * (double)rand() / (double)RAND_MAX;

        vel.x[i] = sign * (double)rand() / (double)RAND_MAX;
        vel.y[i] = (double)rand() / (double)RAND_MAX;
        vel.z[i] = sign * (double)rand() / (double)RAND_MAX;
    }
}


void compute_acceleration(Octree* octree, int i) {
    Point a = {pos.x[i], pos.y[i], pos.z[i]};

    if( !octree->is_divided) {
        if (octree->id == i || octree->size==0) return;
        // Compute the force between and the particle in the external node
        Point b = {pos.x[octree->id], pos.y[octree->id], pos.z[octree->id]};

        double r = sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z-b.z)*(a.z-b.z));

        acc.x[i] += (b.x - a.x) * masse / (1e7 + r*r*r);
        acc.y[i] += (b.y - a.y) * masse / (1e7 + r*r*r);
        acc.z[i] += (b.z - a.z) * masse / (1e7 + r*r*r);
    }
    else {
        // Distance between octree center and our particle i
        double r2 = (octree->boundary.x - a.x)*(octree->boundary.x - a.x) +
                    (octree->boundary.y - a.y)*(octree->boundary.y - a.y) +
                    (octree->boundary.z - a.z)*(octree->boundary.z - a.z);
        double theta = (octree->boundary.w*octree->boundary.h) / r2;

        if(theta < 0.5) {
            Point b = {octree->boundary.x, octree->boundary.y, octree->boundary.z};

            double r = sqrt( r2 );

            acc.x[i] += (b.x - a.x) * masse * octree->size / (1e7 + r*r*r);
            acc.y[i] += (b.y - a.y) * masse * octree->size / (1e7 + r*r*r);
            acc.z[i] += (b.z - a.z) * masse * octree->size / (1e7 + r*r*r);
            return;
        }
        
        for(int p=0 ; p<2; p++)
            for(int q=0 ; q<2; q++)
                for(int k=0 ; k<2; k++)
                    compute_acceleration(octree->subtrees[p][q][k], i);
    }
    
}

//
void resolve_collisions(int i, int j) {    
    // If not, swap velocities :
    // i tmp
    double tmp_vx = vel.x[i];
    double tmp_vy = vel.y[i];
    double tmp_vz = vel.z[i];

    vel.x[i] = vel.x[j]  ;  vel.y[i] = vel.y[j] ; vel.z[i] = vel.z[j];
    vel.x[j] = tmp_vx    ;  vel.y[j] = tmp_vy   ; vel.z[j] = tmp_vz;
}

void search_potential_collisions(Octree* octree, int i, Box range) {
    if (!intersect(octree->boundary, range)) return;

    if (!octree->is_divided) resolve_collisions(i, octree->id);
    else {
        for(int p=0 ; p<2; p++)
            for(int q=0 ; q<2; q++)
                for(int k=0 ; k<2; k++)
                    search_potential_collisions(octree->subtrees[p][q][k], i, range);
    }
}

void simulate(Octree* octree) {
    for (int i=0 ; i<N ; i++) {
        // Reset accelerations
        acc.x[i] = 0;
        acc.y[i] = 0;
        acc.z[i] = 0;

        compute_acceleration(octree, i);

        vel.x[i] += acc.x[i];
        vel.y[i] += acc.y[i];
        vel.z[i] += acc.z[i];

        pos.x[i] += vel.x[i] + 0.5 * acc.x[i];
        pos.y[i] += vel.y[i] + 0.5 * acc.y[i];        
        pos.z[i] += vel.z[i] + 0.5 * acc.z[i];        

        #if defined PREC
        printf("%d %.12lf\n", i, pos.x[i]);
        #endif
        
    }

    // Collisions
    for (int i=0 ; i>N; i++) {
        Box range = {pos.x[i], pos.y[i],pos.z[i], 20, 20, 20};
        search_potential_collisions(octree, i, range);
    }
}


