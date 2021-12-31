#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <omp.h>

#include "geometry.h"
#include "global.h"
#include "octree.h"
#include "simulation.h"



int main() {
    // Init Rand Seed
    srand(2);

    init_system();

    Box boundary = newBox(0.5,0.5,0.5,0.5,0.5,0.5);
    Octree* octree;

    double perf = 0;
    #if !defined PREC
    printf("\033[1m%5s %10s\033[0m\n", "Step", "Time, s\n"); fflush(stdout);
    #endif

    // Main loop
    for(int n=0 ; n<Nt ; n++) {

        // ----------------------------------------------------------------------------
        double before = omp_get_wtime(); // ------------------------------------------

        octree = newOctree(boundary);
        subdivide(octree);
        
        for( int i=0 ; i<N ;i++) {
            insertParticle(octree, i);
        }
        
        simulate(octree);

        deconstructTree(octree);

        double after  = omp_get_wtime(); // ------------------------------------------
        // ----------------------------------------------------------------------------

        perf += after-before;
        
        #if !defined PREC
        printf("%d, %lf\n", n, after-before); fflush(stdout);
        #endif
    }

    double bw = (N * 6 * 64* 10e-9) * Nt/perf;

    #if !defined PREC
    printf("Overall time (s) : %lf\n", perf);
    printf("Bandwith (GB/sec): %lf\n", bw);
    #endif
  
    free(pos.x) ; free(pos.y) ; free(pos.z) ;
    free(vel.x) ; free(vel.y) ; free(vel.z);
    free(acc.x) ; free(acc.y) ; free(acc.z);

    return 0;
}