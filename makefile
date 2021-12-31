CC=gcc
CFLAGS=-Ofast
sdllib=`sdl2-config --cflags --libs`
LFLAGS=-lm -fopenmp


# PERFORMANCE PLOTS
plotPerf500: PERF/500_quad.dat PERF/500_0.dat
	cd PERF && \
	gnuplot -c gnu_script_500.gp && \
	eog perf_500.png
plotPerf1000: PERF/1000_quad.dat PERF/1000_0.dat
	cd PERF && \
	gnuplot -c gnu_script_1000.gp && \
	eog perf_1000.png

# QUAD
quad: QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h makefile
	$(CC) -Ofast -DOVERALLPERF -DSDL $< -o bin/$@ $(sdllib) $(LFLAGS)
quadPERF: QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h makefile
	$(CC) -Ofast -DPERF $< -o bin/$@ $(LFLAGS)
quadPREC: QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h makefile
	$(CC) -DPREC $< -o bin/$@ $(LFLAGS)


# NBODY0
base: nbody0.c
	$(CC) -Ofast -DSDL $< -o bin/$@ $(sdllib) $(LFLAGS)
basePERF: nbody0.c
	$(CC) -Ofast -DPERF $< -o bin/$@ $(LFLAGS)
basePREC: nbody0.c
	$(CC) -DPREC $< -o bin/$@ $(LFLAGS)


# NBODYSOA
soa: nbodySOA.c
	$(CC) -Ofast -DSDL $< -o bin/$@ $(sdllib) $(LFLAGS)
soaPERF: nbodySOA.c
	$(CC) -Ofast -DPERF $< -o bin/$@ $(LFLAGS)
soaPREC: nbodySOA.c
	$(CC) -DPREC $< -o bin/$@ $(LFLAGS)


genBasePerf:
	sudo taskset 2 bin/basePERF 500   > data/files/base500.dat
	sudo taskset 2 bin/basePERF 1000  > data/files/base1000.dat
	sudo taskset 2 bin/basePERF 5000  > data/files/base5000.dat
	sudo taskset 2 bin/basePERF 10000 > data/files/base10000.dat
	sudo taskset 2 bin/basePERF 20000 > data/files/base20000.dat
genSoaPerf:
	sudo taskset 2 bin/soaPERF 500   > data/files/soa500.dat
	sudo taskset 2 bin/soaPERF 1000  > data/files/soa1000.dat
	sudo taskset 2 bin/soaPERF 5000  > data/files/soa5000.dat
	sudo taskset 2 bin/soaPERF 10000 > data/files/soa10000.dat
	sudo taskset 2 bin/soaPERF 20000 > data/files/soa20000.dat
genQuadPerf:
	sudo taskset 2 bin/quadPERF 500   > data/files/quad500.dat
	sudo taskset 2 bin/quadPERF 1000  > data/files/quad1000.dat
	sudo taskset 2 bin/quadPERF 5000  > data/files/quad5000.dat
	sudo taskset 2 bin/quadPERF 10000 > data/files/quad10000.dat
	sudo taskset 2 bin/quadPERF 20000 > data/files/quad20000.dat



# DATA PROCESSING PERFORMANCE
perfProcess: data/data_processing/perf_process.c
	$(CC) $< -o bin/$@
plotPerf: data/data_processing/gnu_perf.gp data/data_processing/perf_process.c
	gnuplot -c $<
	eog perf.png
plotPerfSpeedup: data/data_processing/gnu_perf_speedup.gp data/data_processing/perf_process.c
	gnuplot -c $<
	eog perfSpeedup.png

# DATA PROCESSING PRECISION
precProcess: data/data_processing/prec_process.c
	$(CC) -g $< -o bin/$@
	bin/precProcess 5000 data/files/basePrec data/files/soaPrec data/files/quadPrec
plotPrec: data/data_processing/gnu_prec.gp data/data_processing/prec_process.c
	gnuplot -c $<
	eog prec.png

clean:
	rm -f bin/*
	rm -f a.out
	rm -f *.png
	rm -r maqao*

cleandat:
	rm -f data/files/*