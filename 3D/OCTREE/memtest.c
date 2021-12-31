#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "geometry.h"
#include "global.h"
#include "octreeTree.h"
#include "simulation.h"

int main() {

    Box boundary = newRect(200, 200, 200, 200);
    Octree* octree = newOctree(boundary);
    subdivide(octree);

    init_system();

      for( int i=0 ; i<N ;i++) {
          insertParticle(octree, i);
      }

    deconstructTree(octree);

    free(fluid);

    return 0;
}