/*
  N-BODY collision simulation
  
  Bad code --> optimize
  
*/
// Compile : gcc -o nbody1 nbody1.c -lm `sdl2-config --cflags --libs`

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

//#include "rdtsc.h"

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
vector add_vectors_ASM(vector a, vector b)
{
  vector c = {0,0};
  __asm__ volatile (
      // Initialize registers to zero
      "xorpd %%xmm0, %%xmm0;\n"
      "xorpd %%xmm1, %%xmm1;\n"

      "movapd (%[_a]), %%xmm0;\n"  // xmm0 = a
      "movapd (%[_b]), %%xmm1;\n"  // xmm1 = b

      "addpd %%xmm1, %%xmm0;\n"    // xmm0 += xmm1

      "movapd %%xmm0, (%[_c]);\n"

      : // outputs
      : // inputs
      [_a] "r" (&a),
      [_b] "r" (&b),
      [_c] "r" (&c)
      : //clobber
      "cc", "memory", "xmm0", "xmm1");

  return c;
}

//
vector scale_vector(double b, vector a)
{
  vector c = { b * a.x, b * a.y };
  
  return c;
}

//
vector scale_vector_ASM(double b, vector a)
{
  vector c = {0,0};

  __asm__ volatile (
      "xorpd %%xmm0, %%xmm0;\n"  // xmm0 = {0,0}
      "xorpd %%xmm1, %%xmm1;\n"  // xmm1 = {0,0}

      "movapd (%[_a]), %%xmm0;\n"  // xmm0 = {a.x, a.y}

      // xmm1 = {b, b}
      "addsd (%[_b]), %%xmm1;\n"
      "shufpd $1, %%xmm1, %%xmm1;\n"
      "addsd (%[_b]), %%xmm1;\n"

      "mulpd %%xmm1, %%xmm0;\n"

      "movapd %%xmm0, (%[_c]);\n" //c = xmm0

      : //outputs
      : //inputs
      [_b] "r" (&b),
      [_a] "r" (&a),
      [_c] "r" (&c)
      : //clobber
      "cc", "memory", "xmm0", "xmm1");

  return c;
}


//
vector sub_vectors(vector a, vector b)
{
  vector c = { a.x - b.x, a.y - b.y };
  
  return c;
}


vector sub_vectors_ASM(vector a, vector b)
{
  vector c = {0,0};

  __asm__ volatile(
      "xorpd %%xmm0, %%xmm0;\n"  // xmm0 = {0,0}
      "xorpd %%xmm1, %%xmm1;\n"  // xmm1 = {0,0}

      "movapd (%[_a]), %%xmm0;\n"  // xmm0 = { a.x, a.y }
      "movapd (%[_b]), %%xmm1;\n"  // xmm1 = { b.x, b.y }

      "subpd %%xmm1, %%xmm0;\n"  // xmm0 .-= xmm1

      "movapd %%xmm0, (%[_c]);\n"

      : // outputs
      : // inputs
      [_c] "r" (&c),
      [_a] "r" (&a),
      [_b] "r" (&b)

      : // clobber
      "cc", "memory", "xmm0", "xmm1");
  return c;
}



//
double mod(vector a)
{
  return sqrt(a.x * a.x + a.y * a.y);
}


double mod_ASM(vector a)
{
  double res = 0;

  __asm__ volatile (
      "xorpd %%xmm0, %%xmm0;\n"  // xmm0 = { 0, 0 }
      "xorpd %%xmm1, %%xmm1;\n"  // xmm1 = { 0, 0 }

      "movapd (%[_a]), %%xmm0;\n"  // xmm0 = { a.x, a.y }

      "mulpd %%xmm0, %%xmm0;\n"  // xmm0 .*= xmm0

      // xmm1[0] = xmm0[0] + xmm0[1]
      "addsd %%xmm0, %%xmm1;\n"
      "shufpd $1, %%xmm0, %%xmm0;\n"
      "addsd %%xmm0, %%xmm1;\n"

      "sqrtsd %%xmm1, %%xmm1;\n"  // xmm1[0] = sqrt(xmm1[0])

      "movsd %%xmm1, (%[_res]);\n"

      : //outputs
      : //inputs
      [_a] "r" (&a),
      [_res] "r" (&res)

      : //clobber
      "cc", "memory", "xmm0", "xmm1");

  return res;
}



//
void init_system()
{
  w = h = 800;

  // Number of bodies
  #if defined PERF1000
    nbodies = 1000;
  #else
    nbodies = 500;
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
      // CHECK COORDINATES
      if (positions[i].x == positions[j].x &&
	        positions[i].y == positions[j].y)
        {
        // SWAP VELOCITIES
        vector temp = velocities[i];
        velocities[i] = velocities[j];
        velocities[j] = temp;
        }
}

//
void compute_accelerations_0()
{ 
  vector tmp;
  for (int i = 0; i < nbodies; i++)
    {     
      accelerations[i].x = 0;
      accelerations[i].y = 0;
      tmp = accelerations[i];
      for(int j = 0; j < nbodies; j++){
	      if(i != j)  
          tmp = add_vectors(tmp, scale_vector(GravConstant * masses[j] / (pow(mod(sub_vectors(positions[i], positions[j])), 3) + 1e7), sub_vectors(positions[j], positions[i])));
      }
      accelerations[i] = add_vectors(tmp, accelerations[i]); 
    }
}

//
void compute_accelerations()
{ 
  // Temporary vector declaration
  vector tmp;

  // Reset accelerations at each new time
  for (int i = 0; i < nbodies; i++) {accelerations[i].x = 0 ; accelerations[i].y = 0;}

  // Compute the force between i and j
  for (int i = 0; i < nbodies; i++)
    {     
      for(int j = i+1; j < nbodies; j++){
        tmp = scale_vector(GravConstant * masses[j] / (pow(mod(sub_vectors(positions[i], positions[j])), 3) + 1e7), sub_vectors(positions[j], positions[i]));
        accelerations[i] = add_vectors(accelerations[i], tmp);
        accelerations[j] = sub_vectors(accelerations[j], tmp);
      }
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
  compute_accelerations();  // 64% du temps
  compute_positions();      // ~1%
  compute_velocities();     // ~1%
  resolve_collisions();     // 2% du temps
}

//
int main(int argc, char **argv)
{
  //
  int i;
  unsigned char quit = 0;
  SDL_Event event;
  SDL_Window *window;
  SDL_Renderer *renderer;

  srand(2);
  
  //
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_OPENGL, &window, &renderer);
  
  //
  init_system();
  
  //Main loop
  for (int i = 0; !quit && i < timeSteps; i++)
    {	  
      //
      double before = (double)rdtsc();
      
      simulate();

      //
      double after = (double)rdtsc();
      
      #if defined PERF500
        printf("%d %lf\n", i, (after - before));
      #elif defined PERF1000
        printf("%d %lf\n", i, (after - before));
      #endif

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      
      for (int i = 0; i < nbodies; i++)
	    {
        #if defined PREC
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
    }
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}
