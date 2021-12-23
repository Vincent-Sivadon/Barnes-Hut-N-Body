/*
  N-BODY collision simulation
  
  Bad code --> optimize
  
*/

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#if defined SDL
#include <SDL2/SDL.h>
#endif


//
typedef struct {

  double x, y;
  
} vector;

//
int w, h;

//
int nbodies, timeSteps;

//
double *masses, GravConstant;

//
vector *positions, *velocities, *accelerations;

//
unsigned long long rdtsc(void)
{
  unsigned long long a, d;
  
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
  
  return (d << 32) | a;
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
vector add_vectors(vector a, vector b)
{
  vector c = { a.x + b.x, a.y + b.y };
  
  return c;
}

//
vector scale_vector(double b, vector a)
{
  vector c = { b * a.x, b * a.y };
  
  return c;
}

//
vector sub_vectors(vector a, vector b)
{
  vector c = { a.x - b.x, a.y - b.y };
  
  return c;
}

//
double mod(vector a)
{
  return sqrt(a.x * a.x + a.y * a.y);
}

//
void init_system()
{
  w = h = 800;
  #if defined PERF1000
    nbodies = 1000;
  #else
    nbodies = 1000;
  #endif

  GravConstant = 1;
  timeSteps = 1000;
  
  //
  masses        = malloc(nbodies * sizeof(double));
  positions     = malloc(nbodies * sizeof(vector));
  velocities    = malloc(nbodies * sizeof(vector));
  accelerations = malloc(nbodies * sizeof(vector));

  //
  for (int i = 0; i < nbodies; i++)
    {
      masses[i] = 5;
      
      positions[i].x = randxy(10, w);
      positions[i].y = randxy(10, h);
      
      velocities[i].x = randreal();
      velocities[i].y = randreal();
    }
}

//
void resolve_collisions()
{
  //
  for (int i = 0; i < nbodies - 1; i++)
    for (int j = i + 1; j < nbodies; j++)
      if (positions[i].x == positions[j].x &&
	  positions[i].y == positions[j].y)
	{
	  vector temp = velocities[i];
	  velocities[i] = velocities[j];
	  velocities[j] = temp;
	}
}

//
void compute_accelerations()
{ 
  for (int i = 0; i < nbodies; i++)
    {
      accelerations[i].x = 0;
      accelerations[i].y = 0;
      
      for(int j = 0; j < nbodies; j++)
	if(i != j)
	  accelerations[i] = add_vectors(accelerations[i],
					 scale_vector(GravConstant * masses[j] / (pow(mod(sub_vectors(positions[i], positions[j])), 3) + 1e7),
						      sub_vectors(positions[j], positions[i])));
    }
}


//
void compute_velocities()
{  
  for (int i = 0; i < nbodies; i++)
    velocities[i] = add_vectors(velocities[i], accelerations[i]);
}

//
void compute_positions()
{
  for (int i = 0; i < nbodies; i++)
    positions[i] = add_vectors(positions[i], add_vectors(velocities[i], scale_vector(0.5, accelerations[i])));
}

//
void simulate()
{
  compute_accelerations();
  compute_positions();
  compute_velocities();
  resolve_collisions();
}

//
int main(int argc, char **argv)
{
  srand(2);

  //
  int i;
  unsigned char quit = 0;
  #if defined SDL
  SDL_Event event;
  SDL_Window *window;
  SDL_Renderer *renderer;

  //
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_OPENGL, &window, &renderer);
  #endif

  //
  init_system();

  double perf = 0;
  
  //Main loop
  for (int i = 0; !quit && i < timeSteps; i++)
    {	  
      //
      double before = omp_get_wtime();
      
      simulate();

      //
      double after = omp_get_wtime();
      perf += after-before;
    
      #ifdef PERF500
        printf("%d %lf\n", i, (after - before));
      #elif defined PERF1000
        printf("%d %lf\n", i, (after - before));
      #endif

      #if defined SDL
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      
      for (int i = 0; i < nbodies; i++)
	    {
        #ifdef PREC
          printf("%.12lf\n", positions[i].x);
        #endif
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, positions[i].x, positions[i].y);
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

    double bw = (nbodies * 6 * 64* 10e-9) * timeSteps/perf;
    printf("Overall time (s) : %lf\n", perf);
    printf("Bandwidth (GB/s) : %lf\n", bw);
  
  #if defined SDL
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  #endif

  return 0;
}
