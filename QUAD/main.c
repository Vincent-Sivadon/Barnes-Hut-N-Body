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


// RDTSC
unsigned long long rdtsc(void)
{
  unsigned long long a, d;
  
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
  
  return (d << 32) | a;
}


int main() {
    // Init Rand Seed
    srand(2);

    unsigned char quit = 0;
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;

    init_system();

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_OPENGL, &window, &renderer);



    Rect boundary = newRect(WIDTH/2,HEIGHT/2,WIDTH/2,HEIGHT/2);
    Quad* quad;

    double perf = 0;

    // Main loop
    for(int i=0 ; !quit && i<Nt ; i++) {
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // ----------------------------------------------------------------------------
        double before = (double) rdtsc(); // ------------------------------------------

        quad = newQuad(boundary);
        subdivide(quad);
        
        
        for( int i=0 ; i<N ;i++) {
            insertParticle(quad, i);
        }
        

        simulate(quad);

        //drawQuad(renderer, quad);

        deconstructTree(quad);

        double after  = (double) rdtsc(); // ------------------------------------------
        // ----------------------------------------------------------------------------

        perf += after-before;
        
        #if defined PERF1000
            printf("%d %lf\n", i, (after - before));
        #elif defined PERF500
            printf("%d %lf\n", i, (after - before));
        #endif

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Draw every particle
        for(int i=0 ; i<N ; i++){
            #if defined PREC
                printf("%.12lf\n", fluid[i].pos.x);
            #endif

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer, fluid[i].pos.x, fluid[i].pos.y);
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event))
        if (event.type == SDL_QUIT)
            quit = 1;
        else
            if (event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_q)
                quit = 1;

    }
    #if defined OVERALLPERF
        printf("Overall cycles time : %lf\n", perf);
    #endif
  
    free(fluid);

    // CLEAN
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}