#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <omp.h>

#if defined SDL
#include <SDL2/SDL.h>
#endif

#include "geometry.h"
#include "global.h"
#include "quadTree.h"
#include "simulation.h"



int main() {
    // Init Rand Seed
    srand(2);

    init_system();

    unsigned char quit = 0;
    #if defined SDL
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;


    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_OPENGL, &window, &renderer);
    #endif

    Rect boundary = newRect(WIDTH/2,HEIGHT/2,WIDTH/2,HEIGHT/2);
    Quad* quad;

    double perf = 0;

    // Main loop
    for(int i=0 ; !quit && i<Nt ; i++) {
        #if defined SDL
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        #endif

        // ----------------------------------------------------------------------------
        double before = omp_get_wtime(); // ------------------------------------------

        quad = newQuad(boundary);
        subdivide(quad);
        
        
        for( int i=0 ; i<N ;i++) {
            insertParticle(quad, i);
        }
        

        simulate(quad);

        //drawQuad(renderer, quad);

        deconstructTree(quad);

        double after  = omp_get_wtime(); // ------------------------------------------
        // ----------------------------------------------------------------------------

        perf += after-before;
        
        #if defined PERF1000
            printf("%d %lf\n", i, (after - before));
        #elif defined PERF500
            printf("%d %lf\n", i, (after - before));
        #endif

        #if defined SDL
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
        #endif

    }

    double bw = (N * 6 * 64* 10e-9) * Nt/perf;

    #if defined OVERALLPERF
        printf("Overall time (s) : %lf\n", perf);
        printf("Bandwith (GB/sec): %lf\n", bw);
    #endif
  
    free(fluid);

    // CLEAN
    #if defined SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    #endif

    return 0;
}