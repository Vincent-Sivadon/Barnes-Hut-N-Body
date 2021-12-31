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
double *masses, G;

//
Field positions, velocities, accelerations;

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
    G = 1;
    Nt = 10;

    //
    masses = malloc(N * sizeof(double));

    // Field Declaration
    decl_field(N, &positions);
    decl_field(N, &velocities);
    decl_field(N, &accelerations);

    for(int i=0; i<N ; i++)
    {
        masses[i] = 5;

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

double mod(int i, int j){
    return sqrt(
            (positions.x[i] - positions.x[j]) * (positions.x[i] - positions.x[j]) +
            (positions.y[i] - positions.y[j]) * (positions.y[i] - positions.y[j])
        );
}


void compute_accelerations()
{
    // Temporary vector
    double tmp_x = 0;
    double tmp_y = 0;

    for (int i=0 ; i<N ; i++) {accelerations.x[i] = 0; accelerations.y[i]=0; }

    for(int i=0 ; i<N ; i++){  
        for(int j=i+1 ; j<N ; j++){
            // Distance between body i and body j
            double r = mod(i,j);

            // Compute acceleration between i and j
            tmp_x = tmp_y = G * masses[j] / (1e7 + pow(r, 3));

            // X
            tmp_x *= (positions.x[j] - positions.x[i]);
            accelerations.x[i] += tmp_x;
            accelerations.x[j] -= tmp_x;

            // Y
            tmp_y *= (positions.y[j] - positions.y[i]);
            accelerations.y[i] += tmp_y;
            accelerations.y[j] -= tmp_y;
        }
    }
}



//
void compute_velocities()
{
    for(int i=0 ; i<N ; i++)
    {
        velocities.x[i] += accelerations.x[i];
        velocities.y[i] += accelerations.y[i];
    }
}

void compute_positions()
{
    for(int i=0 ; i<N ; i++)
    {
        positions.x[i] += velocities.x[i] + 0.5 * accelerations.x[i];
        positions.y[i] += velocities.y[i] + 0.5 * accelerations.y[i];
    
        #if defined PREC
        printf("%.12lf %.12lf\n", positions.x[i], positions.y[i]);
        #endif
    }
}

void simulate()
{
  compute_accelerations();
  compute_velocities();
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
        
    // Main loop
    for(int i=0 ; !quit && i<Nt ; i++)
    {
        // CORE
        double before = omp_get_wtime();
        simulate();
        double after  = omp_get_wtime();

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

    #if defined SDL
    // CLEAN
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    #endif

    return 0;
}