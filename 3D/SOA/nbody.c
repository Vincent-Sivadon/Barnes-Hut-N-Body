//
#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//
typedef float              f32;
typedef double             f64;
typedef unsigned long long u64;

const f32 softening = 1e-20;
const u64 steps     = 10;    // Number of iterations
const f32 dt        = 0.01;  // Time step


//
typedef struct particle_s {

  f32 x, y, z;
  f32 vx, vy, vz;
  
} particle_t;

typedef struct {
  f32 *x, *y, *z;
} Field;


void allocateField(Field* field, u64 n) {
  field->x = malloc(sizeof(f32) * n);
  field->z = malloc(sizeof(f32) * n);
  field->y = malloc(sizeof(f32) * n);
}

Field pos, vel;

//
void init(u64 n)
{
  allocateField(&pos, n);
  allocateField(&vel, n);

  for (int i=0 ; i<n ; i++) {
      // Rand
      u64 r1 = (u64)rand();
      u64 r2 = (u64)rand();
      f32 sign = (r1 > r2) ? 1 : -1;
  
      //
      pos.x[i] = sign * (f32)rand() / (f32)RAND_MAX;
      pos.y[i] =        (f32)rand() / (f32)RAND_MAX;
      pos.z[i] = sign * (f32)rand() / (f32)RAND_MAX;

      vel.x[i] = sign * (f32)rand() / (f32)RAND_MAX;
      vel.x[i] =        (f32)rand() / (f32)RAND_MAX;
      vel.x[i] = sign * (f32)rand() / (f32)RAND_MAX;
  }
}

//
void move_particles(u64 n)
{
  //
  const f32 softening = 1e-20;

  //
  for (u64 i = 0; i < n; i++) {
      // forces components
      f32 fx = 0.0;
      f32 fy = 0.0;
      f32 fz = 0.0;

      //23 floating-point operations
      for (u64 j = 0; j < n; j++) {
        //Newton's law
        const f32 dx = vel.x[j] - vel.x[i]; //1
        const f32 dy = vel.y[j] - vel.y[i]; //2
        const f32 dz = vel.z[j] - vel.z[i]; //3
        const f32 d2 = (dx * dx) + (dy * dy) + (dz * dz) + softening; //9
        const f32 d = sqrt(d2);
        const f32 d2over3 = 1/(d*d*d);

        //Net force
        fx += dx * d2over3; //13
        fy += dy * d2over3; //15
        fz += dz * d2over3; //17
	    }

      //
      vel.x[i] += dt * fx; //19
      vel.y[i] += dt * fy; //21
      vel.z[i] += dt * fz; //23

      pos.x[i] += dt * vel.x[i];
      pos.y[i] += dt * vel.y[i];
      pos.z[i] += dt * vel.z[i];

    }
}

//
int main(int argc, char **argv)
{
  // Parameters (Simulation)
  const u64 n = (argc > 1) ? atoll(argv[1]) : 16384;  // Number of bodies

  //
  f64 rate = 0.0, drate = 0.0;

  //Steps to skip for warm up (to make sure the data comes from cache and not RAM)
  const u64 warmup = 3;
  
  // Allocate array of all particles
  particle_t *p = malloc(sizeof(particle_t) * n);

  // Initialize Simulation
  init(n);

  // Total memory size
  const u64 s = sizeof(particle_t) * n;
  
  printf("\n\033[1mTotal memory size:\033[0m %llu B, %llu KiB, %llu MiB\n\n", s, s >> 10, s >> 20);
  
  //
  printf("\033[1m%5s %10s %10s %8s\033[0m\n", "Step", "Time, s", "Interact/s", "GFLOP/s"); fflush(stdout);
  
  //
  for (u64 i = 0; i < steps; i++)
    {
      //Measure
      const f64 start = omp_get_wtime();

      move_particles(n);

      const f64 end = omp_get_wtime();

      //Number of interactions/iterations
      const f32 h1 = (f32)(n) * (f32)(n - 1);

      //GFLOPS
      const f32 h2 = (23.0 * h1 + 3.0 * (f32)n) * 1e-9;
      
      if (i >= warmup)
	{
	  rate += h2 / (end - start);
	  drate += (h2 * h2) / ((end - start) * (end - start));
	}

      //
      printf("%5llu %10.3e %10.3e %8.1f %s\n",
	     i,
	     (end - start),
	     h1 / (end - start),
	     h2 / (end - start),
	     (i < warmup) ? "*" : "");
      
      fflush(stdout);
    }

  //
  rate /= (f64)(steps - warmup);
  drate = sqrt(drate / (f64)(steps - warmup) - (rate * rate));

  printf("-----------------------------------------------------\n");
  printf("\033[1m%s %4s \033[0;36m%10.1lf +- %.1lf GFLOP/s\033[0;36m\n",
	 "Average performance:", "", rate, drate);
  printf("-----------------------------------------------------\n");
  
  //
  free(p);

  //
  return 0;
}
