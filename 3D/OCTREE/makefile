all: octree
CFLAGS=-march=native -mavx2 -Ofast -fopt-info-all=nbody.gcc.optrpt
LFLAGS=-lm -fopenmp

octree: main.c geometry.h global.h octree.h simulation.h
	gcc $(CFLAGS) $< -o $@ $(LFLAGS)

octree_debug: main.c geometry.h global.h octree.h simulation.h
	gcc -march=native -mavx2 -O1 -g $< -o $@ $(LFLAGS)

clean:
	rm -Rf *~ octree *.optrpt

