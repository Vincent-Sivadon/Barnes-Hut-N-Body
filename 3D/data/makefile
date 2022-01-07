

perfProcess: data_processing/perfProcess.c
	gcc -o perfProcess $<
plotPerf: data_processing/perfProcess.c files/*
	gnuplot -c data_processing/gnu_perf.gp
	eog perf.png
plotPerfSpeedup: data_processing/perfProcess.c files/*
	gnuplot -c data_processing/gnu_perf_speedup.gp
	eog perfSpeedup.png
