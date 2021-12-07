CC=gcc
CFLAGS=-Ofast
sdllib=`sdl2-config --cflags --libs`


# PERFORMANCE PLOTS
plotPerf500: PERF/500_quad.dat PERF/500_0.dat
	cd PERF && \
	gnuplot -c gnu_script_500.gp && \
	eog perf_500.png
plotPerf1000: PERF/1000_quad.dat PERF/1000_0.dat
	cd PERF && \
	gnuplot -c gnu_script_1000.gp && \
	eog perf_1000.png

# QUAD DATA GENERATION
genPerf500quad: QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h
	$(CC) -Ofast -DPERF500 QUAD/main.c -o quad $(sdllib) -lm
	sudo taskset -c 2 ./quad > PERF/500_quad.dat
genPerf1000quad: QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h
	$(CC) -Ofast -DPERF1000 QUAD/main.c -o quad $(sdllib) -lm
	sudo taskset -c 2 ./quad > PERF/1000_quad.dat
genPRECquad: QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h
	$(CC) -DPREC QUAD/main.c -o quad $(sdllib) -lm
	sudo taskset -c 2 ./quad > PRECISION/quad.dat
quad: QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h makefile
	$(CC) -Ofast -DOVERALLPERF QUAD/main.c -o quad $(sdllib) -lm
#sudo taskset -c 2 ./quad
memtest: QUAD/memtest.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h makefile
	$(CC) -pg QUAD/memtest.c -o memtest $(sdllib) -lm

# NBODY0 DATA GENERATION
genPerf500_0: nbody0.c
	$(CC) -DPERF500 nbody0.c -o nbody0 $(sdllib) -lm
	sudo taskset -c 2 ./nbody0 > PERF/500_0.dat
genPerf1000_0: nbody0.c
	$(CC) -DPERF1000 nbody0.c -o nbody0 $(sdllib) -lm
	sudo taskset -c 2 ./nbody0 > PERF/1000_0.dat
genPREC_0: nbody0.c
	$(CC) -DPREC nbody0.c -o nbody0 $(sdllib) -lm
	sudo taskset -c 2 ./nbody0 > PRECISION/0.dat

# NBODYSOA DATA GENERATION
genPREC_SOA: nbodySOA.c
	$(CC) -DPREC nbodySOA.c -o nbodySOA $(sdllib) -lm
	sudo taskset -c 2 ./nbodySOA > PRECISION/SOA.dat



comp_quad: PRECISION/comparaison.c PRECISION/0.dat PRECISION/quad.dat
	cd PRECISION && \
	$(CC) -DQUAD comparaison.c -o comparaison && \
	./comparaison > deltas.dat && \
	gnuplot -c gnu_script_quad.gp && \
	eog precision_quad.png
comp_SOA: PRECISION/comparaison.c PRECISION/SOA.dat PRECISION/0.dat
	cd PRECISION && \
	$(CC) -DSOA comparaison.c -o comparaison && \
	./comparaison > deltas.dat && \
	gnuplot -c gnu_script_SOA.gp && \
	eog precision_SOA.png


base:  nbody0.c
	$(CC) $< -o nbody0 $(sdllib) -lm


SOA: nbodySOA.c
	$(CC) $(CFLAGS) $< -o nbodySOA $(sdllib) -lm

AOS: nbody1.c
	$(CC) $(CFLAGS) $< -o nbody1 $(sdllib) -lm

test_quad2: QUAD/test.c QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h
	$(CC) QUAD/test.c -o test_quad2 $(sdllib) -lm


clean:
	rm -f nbody1 nbodySOA nbody0 quad quad2 memtest a.out