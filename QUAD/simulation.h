#pragma once

#include "quadTree.h"
#include "global.h"
#include "quadTree.h"


// RANDOM FUNCTIONS
int randxy(int x, int y)
{
  return (rand() % (y - x + 1)) + x; 
}
double randreal()
{
  int s = (randxy(0, 1)) ? 1 : -1;
  int a = randxy(1, RAND_MAX), b = randxy(1, RAND_MAX);

  return s * ((double)a / (double)b); 
}
double randD(double shift, double width) {
    return shift + width * (double) rand() / (double) RAND_MAX;
}

//
void init_system() {
    //
    WIDTH = HEIGHT = 800;

    // Number of bodies
    #if defined PERF1000
        N = 1000;
    #else 
        N = 500;
    #endif

    Nt = 1000;
    masse = 5;

    // Pointer to all particles
    fluid = malloc(N * sizeof(Particle));

    // for every particles
    for(int i=0; i<N ; i++) {
        fluid[i].pos.x = randxy(10, WIDTH);
        fluid[i].pos.y = randxy(10, HEIGHT);

        fluid[i].vel.x = randreal();
        fluid[i].vel.y = randreal();
    }
}


void force(int i, Point j, double m) {
    //
    double r = mod(fluid[i].pos, j);
    
    //
    fluid[i].acc.x += (j.x - fluid[i].pos.x) * m / (1e7 + pow(r, 3));
    fluid[i].acc.y += (j.y - fluid[i].pos.y) * m / (1e7 + pow(r, 3));
}


void compute_acceleration(Quad* quad, int i) {
    if( !quad->is_divided) {
        if (quad->id == i || quad->size==0) return;
        // Compute the force between and the particle in the external node
        Point j = fluid[quad->id].pos;
        force(i, j, masse);
    }
    else {
        // Distance between quad center and our particle i
        double r2 = pow(quad->boundary.x - fluid[i].pos.x, 2) +
                    pow(quad->boundary.y - fluid[i].pos.y, 2);
        double theta = pow(2*quad->boundary.w,2) / r2;

        if(theta < 0.5) {
            //Point cm = centerOfMass(quad);
            //cm.x = cm.x / quad->size;
            //cm.y = cm.y / quad->size;

            Point quad_center = {quad->boundary.x, quad->boundary.y};
            force(i, quad_center, masse * quad->size);
            return;
        }
        compute_acceleration(quad->northwest, i);
        compute_acceleration(quad->northeast, i);
        compute_acceleration(quad->southwest, i);
        compute_acceleration(quad->southeast, i);
    }
    
}

//
void resolve_collisions(int i, int j) {    
    // If not, swap velocities :
    Point tmp = fluid[i].vel;
    fluid[i].vel = fluid[j].vel;
    fluid[j].vel = tmp;
}

void search_potential_collisions(Quad* quad, int i, Rect range) {
    if (!intersect(quad->boundary, range)) return;

    if (!quad->is_divided) resolve_collisions(i, quad->id);
    else {
        search_potential_collisions(quad->northwest, i, range);
        search_potential_collisions(quad->northeast, i, range);
        search_potential_collisions(quad->southwest, i, range);
        search_potential_collisions(quad->southeast, i, range);
    }
}

void simulate(Quad* quad) {
    for (int i=0 ; i<N ; i++) {
        // Reset accelerations
        fluid[i].acc.x = 0;
        fluid[i].acc.y = 0;

        compute_acceleration(quad, i);

        fluid[i].vel.x += fluid[i].acc.x;
        fluid[i].vel.y += fluid[i].acc.y;

        fluid[i].pos.x += fluid[i].vel.x + 0.5 * fluid[i].acc.x;
        fluid[i].pos.y += fluid[i].vel.y + 0.5 * fluid[i].acc.y;        
        
    }

    // Collisions
    for (int i=0 ; i>N; i++) {
        Rect range = {fluid[i].pos.x, fluid[i].pos.y, 20, 20};
        search_potential_collisions(quad, i, range);
    }
}


