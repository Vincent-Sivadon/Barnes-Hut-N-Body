/*
  N-BODY collision simulation using Struct of Arrays
*/
// Compile : gcc -o nbodySOA nbodySOA.c -lm `sdl2-config --cflags --libs`

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#if defined SDL
#include <SDL2/SDL.h>
#endif

typedef struct {
    double *x;
    double *y;
} Field;



// GLOBAL VARIABLES ------------------------------------------------
// Dimensions of window
int w, h;

//
int N;   // Number of bodies
int Nt;  // Number of time steps


//
Field positions, velocities;

// -----------------------------------------------------------------

double* decl_field(int N, Field* field){
    field->x = malloc(N * sizeof(double));
    field->y = malloc(N * sizeof(double));
}


//
int randxy(int x, int y)
{
  return (rand() % (y - x + 1)) + x; 
}

//
double randreal()
{
  int s = (randxy(0, 1)) ? 1 : -1;
  int a = randxy(1, RAND_MAX), b = randxy(1, RAND_MAX);

  return s * ((double)a / (double)b); 
}


//
void init_system(int nbodies)
{
    w = h = 800;
    N = nbodies;
    Nt = 10;

    // Field Declaration
    decl_field(N, &positions);
    decl_field(N, &velocities);

    for(int i=0; i<N ; i++)
    {
        positions.x[i] = randxy(10, w);
        positions.y[i] = randxy(10, h);

        velocities.x[i] = randreal();
        velocities.y[i] = randreal();
    }
}


//
unsigned long long rdtsc(void)
{
  unsigned long long a, d;
  
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
  
  return (d << 32) | a;
}


//
void resolve_collisions()
{
    //
    for(int i=0 ; i<N-1 ; i++){
        for(int j=i+1; j<N ; j++){
            // CHECK COORDINATES
            if (positions.x[i] == positions.x[j] &&
                positions.y[i] == positions.y[j])
                {
                    // SWAP VELOCITIES

                    // Tmp vector
                    double tmp_x = velocities.x[i];
                    double tmp_y = velocities.y[i];

                    // Vector i = Vector j
                    velocities.x[i] = velocities.x[j];
                    velocities.y[i] = velocities.y[j];

                    // Vector j = Vector tmp
                    velocities.x[j] = tmp_x;
                    velocities.y[j] = tmp_y;
                }
        }
    }
}



void compute_accelerations()
{
    for(int i=0 ; i<N ; i++)
    {
        // Reset accelerations  
        double fx = 0;
        double fy = 0;

        // Already access i coords to limit memory access
        double xi = positions.x[i];
        double yi = positions.y[i];

        for(int j=0 ; j<N ; j++)
        {
                
            double xj = positions.x[j];
            double yj = positions.y[j];

            double dx = xi - xj;
            double dy = yi - yj;
            double r = sqrt(dx*dx + dy*dy);
            double r3inv = 1/(r*r*r + 1e7);

            fx += dx * 5 * r3inv;
            fy += dy * 5 * r3inv;
        }
        velocities.x[i] += fx;
        velocities.y[i] += fy;
    }
}

void compute_positions()
{
    for(int i=0 ; i<N ; i++)
    {
        positions.x[i] += velocities.x[i];
        positions.y[i] += velocities.y[i];
    
        #if defined PREC
        printf("%.12lf %.12lf\n", positions.x[i], positions.y[i]);
        #endif
    }
}

void simulate()
{
  compute_accelerations();
  compute_positions();
  resolve_collisions();
}

int main(int argc, char **argv)
{
    if (argc<2) { printf("Usage : %s [nbodies]\n", argv[0]); return 1;}
    int nbodies = atoi(argv[1]);

    srand(2);

    //
    int i;
    unsigned char quit = 0;
    #if defined SDL
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;



    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_OPENGL, &window, &renderer);
    #endif

    //
    init_system(nbodies);

    double perf = 0;
        
    // Main loop
    for(int i=0 ; !quit && i<Nt ; i++)
    {
        // CORE
        double before = omp_get_wtime();
        simulate();
        double after  = omp_get_wtime();

        perf += (after-before);

        #if defined PERF
        printf("%d %lf\n", i, (after - before));
        #endif

        #if defined SDL
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for(int i=0 ; i<N ; i++)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer, positions.x[i], positions.y[i]);
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

    //printf("Temps moyen d'iteration (s) : %lf\n", perf/Nt);

    #if defined SDL
    // CLEAN
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    #endif

    return 0;
}