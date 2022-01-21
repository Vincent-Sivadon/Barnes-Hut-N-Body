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


// Initialise les paramètres de la simulation et alloue l'espace mémoire nécessaire
void init_system(int nbodies) {
    // Dimensions de la fenêtre (SDL)
    WIDTH = 800;
    HEIGHT = 800;

    N = nbodies; // Nombre de corps
    Nt = 10;     // Nombre de pas de temps
    masse = 5;   // Masse de chaque corps

    // Allocation des tableaux contenants les positions et vitesses de chaque corps
    pos.x = malloc(N * sizeof(double));
    pos.y = malloc(N * sizeof(double));
    vel.x = malloc(N * sizeof(double));
    vel.y = malloc(N * sizeof(double));

    // for every particles
    for(int i=0; i<N ; i++) {
        // Random position
        pos.x[i] = randxy(10, WIDTH);
        pos.y[i] = randxy(10, HEIGHT);

        // Random velocity
        vel.x[i] = randreal();
        vel.y[i] = randreal();
    }
}

// Compute the acceleration for i
// ax, ay i's acceleration componants
void compute_acceleration(Quad* quad, int i, double* ax, double* ay) {
    // Get coords one time
    double ix = pos.x[i];
    double iy = pos.y[i];

    // if quad divided
    if( !quad->is_divided) {
        if (quad->id == i || quad->size==0) return;
        // Compute the force between and the particle in the external node
        double jx = pos.x[quad->id];
        double jy = pos.y[quad->id];

        // distance between those two
        double r = sqrt(
            (ix - jx)*(ix - jx) +
            (iy - jy)*(iy - jy)
        );

        // update acceleration
        *ax += (jx - ix) * masse / (1e7 + r*r*r);
        *ay += (jy - iy) * masse / (1e7 + r*r*r);
    }
    // If divided, then see if we can approximate, or go deeper in the tree
    else {  
        // Distance between quad center and our particle i
        double r2 = (quad->boundary.x - ix)*(quad->boundary.x - ix) +
                    (quad->boundary.y - iy)*(quad->boundary.y - iy);
        // Solid angle between i and the quad
        double theta = (quad->boundary.w * quad->boundary.w) / r2;

        // Critère d'approximation
        if(theta < 0.5) {
            double jx = quad->boundary.x;
            double jy = quad->boundary.y;

            // Distance
            double r = sqrt( r2 );

            *ax += (jx - ix) * masse * quad->size / (1e7 + r*r*r);
            *ay += (jy - iy) * masse * quad->size / (1e7 + r*r*r);
            return;
        }

        // If we can't approximate, go deeper in the tree
        compute_acceleration(quad->northwest, i, ax, ay);
        compute_acceleration(quad->northeast, i, ax, ay);
        compute_acceleration(quad->southwest, i, ax, ay);
        compute_acceleration(quad->southeast, i, ax, ay);
    }
}

// Swap velocities between i and j if collision occures
void resolve_collisions(int i, int j) {   
    // If no collision, than go out
    if (pos.x[i] != pos.x[j] || pos.y[i] != pos.y[j]) return;

    // If collision : swap velocities
    double tmp_vx = vel.x[i];
    double tmp_vy = vel.y[i];

    vel.x[i] = vel.x[j]  ;  vel.y[i] = vel.y[j];
    vel.x[j] = tmp_vx    ;  vel.y[j] = tmp_vy;
}

// Try to limit collision computation by checking if the quad is far enough
// range is a rectangle centered on i
// i is the body on wich we check collisions
void search_potential_collisions(Quad* quad, int i, Rect range) {
    // if too far, then we don't care
    if (!intersect(quad->boundary, range)) return;

    // if close enough and external, than check collision
    if (!quad->is_divided) resolve_collisions(i, quad->id);
    // if close enough but divided, go deeper in the tree
    else {
        search_potential_collisions(quad->northwest, i, range);
        search_potential_collisions(quad->northeast, i, range);
        search_potential_collisions(quad->southwest, i, range);
        search_potential_collisions(quad->southeast, i, range);
    }
}

// Update bodies' positions
void simulate(Quad* quad) {
    for (int i=0 ; i<N ; i++) {
        // Reset accelerations
        double ax = 0;
        double ay = 0;

        // compute i's acceleration
        compute_acceleration(quad, i, &ax, &ay);

        // update i's speed
        vel.x[i] += ax;
        vel.y[i] += ay;

        // update i's position
        pos.x[i] += vel.x[i] + 0.5 * ax;
        pos.y[i] += vel.y[i] + 0.5 * ay;        

        #if defined PREC
        printf("%.12lf %.12lf\n",pos.x[i], pos.y[i]);
        #endif
        
    }

    // Collisions
    for (int i=0 ; i>N; i++) {
        // Rectangle centered on i
        Rect range = {pos.x[i], pos.y[i], 20, 20};

        //
        search_potential_collisions(quad, i, range);
    }
}


