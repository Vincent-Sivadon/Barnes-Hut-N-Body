all: nbody.g nbody.i
CFLAGS=-march=native -mavx2 -Ofast -fopt-info-all=nbody.gcc.optrpt
LFLAGS=-lm -fopenmp

nbody.g: nbody.c
	gcc $(CFLAGS) $< -o $@ $(LFLAGS)

nbodyPREC: nbody.c
	gcc $(CFLAGS) -DPREC $< -o $@ $(LFLAGS)


nbody.i: nbody.c
	icc -xhost -Ofast -qopt-report $< -o $@ -qmkl -qopenmp

clean:
	rm -Rf *~ nbody.g nbody.i *.optrpt

