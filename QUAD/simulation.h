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
void init_system(int nbodies) {
    //
    WIDTH = 800;
    HEIGHT = 800;

    N = nbodies;

    Nt = 10;
    masse = 5;

    // Pointer to all particles
    pos.x = malloc(N * sizeof(double));
    pos.y = malloc(N * sizeof(double));
    vel.x = malloc(N * sizeof(double));
    vel.y = malloc(N * sizeof(double));
    acc.x = malloc(N * sizeof(double));
    acc.y = malloc(N * sizeof(double));

    // for every particles
    for(int i=0; i<N ; i++) {
        pos.x[i] = randxy(10, WIDTH);
        pos.y[i] = randxy(10, HEIGHT);

        vel.x[i] = randreal();
        vel.y[i] = randreal();
    }
}


void compute_acceleration(Quad* quad, int i) {
    Point a = {pos.x[i], pos.y[i]};

    if( !quad->is_divided) {
        if (quad->id == i || quad->size==0) return;
        // Compute the force between and the particle in the external node
        Point b = {pos.x[quad->id], pos.y[quad->id]};

        double r = sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));

        acc.x[i] += (b.x - a.x) * masse / (1e7 + r*r*r);
        acc.y[i] += (b.y - a.y) * masse / (1e7 + r*r*r);
    }
    else {
        // Distance between quad center and our particle i
        double r2 = (quad->boundary.x - a.x)*(quad->boundary.x - a.x) +
                    (quad->boundary.y - a.y)*(quad->boundary.y - a.y);
        double theta = (quad->boundary.w * quad->boundary.w) / r2;

        if(theta < 0.5) {
            Point b = {quad->boundary.x, quad->boundary.y};

            double r = sqrt( r2 );

            acc.x[i] += (b.x - a.x) * masse * quad->size / (1e7 + r*r*r);
            acc.y[i] += (b.y - a.y) * masse * quad->size / (1e7 + r*r*r);
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
    // i tmp
    double tmp_vx = vel.x[i];
    double tmp_vy = vel.y[i];

    vel.x[i] = vel.x[j]  ;  vel.y[i] = vel.y[j];
    vel.x[j] = tmp_vx    ;  vel.y[j] = tmp_vy;
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
        acc.x[i] = 0;
        acc.y[i] = 0;

        compute_acceleration(quad, i);

        vel.x[i] += acc.x[i];
        vel.y[i] += acc.y[i];

        pos.x[i] += vel.x[i] + 0.5 * acc.x[i];
        pos.y[i] += vel.y[i] + 0.5 * acc.y[i];        

        #if defined PREC
        printf("%.12lf %.12lf\n",pos.x[i], pos.y[i]);
        #endif
        
    }

    // Collisions
    for (int i=0 ; i>N; i++) {
        Rect range = {pos.x[i], pos.y[i], 20, 20};
        search_potential_collisions(quad, i, range);
    }
}


