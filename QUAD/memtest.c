#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "geometry.h"
#include "global.h"
#include "quadTree.h"
#include "simulation.h"

int main() {

    Rect boundary = newRect(200, 200, 200, 200);
    Quad* quad = newQuad(boundary);
    subdivide(quad);

    init_system();

      for( int i=0 ; i<N ;i++) {
          insertParticle(quad, i);
      }

    deconstructTree(quad);

    free(fluid);

    return 0;
}