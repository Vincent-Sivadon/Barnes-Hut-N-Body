##############################################################################
##
##  	Il y a 3 versions de la simulation des N-corps dans ce dossier :
##  		- Une première version de base à optimiser (base ou 0)
##  		- Une version Struct of Arrays (SOA)
##  		- Une version Barnes-Hut (QUAD)
##
########################## STRUCTURE DU DOSSIER ##############################
##
##			- bin        : executables
##			- data 
##				- data_processing : scripts C et gnuplot de process des données
##				- files 		  : données .dat
##			- QUAD       : codes de la simulation par Barnes-Hut
##		
##			- nbody0.c   : code de base à optimiser
##			- nbody1.c   : code avec version assembleur
##			- nbodySOA.c : version Struct of Array (SOA)
##
##############################################################################
########################## STRUCTURE DU MAKEFILE ##############################
##		
##		Pour chaque version du code il y a une target pour générer :
##			- la version standarde du code (quad, base, soa)
##			- une version qui donne des informations sur les performances (quadPERF, basePERF, soaPERF, asmPERF)
##			- une version qui donne des outils de comparaison de précision (quadPREC, basePREC, soaPREC)
##			- une macro de génération de fichiers de données (genQuadPerf, genBasePerf, genSoaPerf)
##		Il existe enfin des macro de génération de graphe
##			- perfProcess et precProcess pour traiter les données
##			- plotPerfSpeedup, plotPerf, plotPrec, pour générer les graphe
##		
##############################################################################


CC=gcc
CFLAGS=-Ofast
sdllib=`sdl2-config --cflags --libs`
LFLAGS=-lm -fopenmp


# QUAD : generation des executables de la simulation par Barnes-Hut
# version standard avec visualisation
quad: QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h makefile
	$(CC) -Ofast -DOVERALLPERF -DSDL $< -o bin/$@ $(sdllib) $(LFLAGS)
# version générant des rapports de performances
quadPERF: QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h makefile
	$(CC) -Ofast -DPERF $< -o bin/$@ $(LFLAGS)
# version répertoriant la position de chaque particule à chaque temps (pour pouvoir comparer)
quadPREC: QUAD/main.c QUAD/geometry.h QUAD/global.h QUAD/quadTree.h QUAD/simulation.h makefile
	$(CC) -DPREC $< -o bin/$@ $(LFLAGS)


# NBODY0 : generation des executables du code de base
# version standard avec visualisation
base: nbody0.c
	$(CC) -Ofast -DSDL $< -o bin/$@ $(sdllib) $(LFLAGS)
# version générant des rapports de performances
basePERF: nbody0.c
	$(CC) -Ofast -DPERF $< -o bin/$@ $(LFLAGS)
# version répertoriant la position de chaque particule à chaque temps (pour pouvoir comparer)
basePREC: nbody0.c
	$(CC) -DPREC $< -o bin/$@ $(LFLAGS)

# ASSMEBLY :
#
asmPERF: nbodyASM.c
	$(CC) -Ofast $< -o bin/$@ $(sdllib) $(LFLAGS)

# NBODYSOA : generation des executables de la version Struct Of Arrays (SOA)
# version standard avec visualisation
soa: nbodySOA.c
	$(CC) -Ofast -DSDL $< -o bin/$@ $(sdllib) $(LFLAGS)
# version générant des rapports de performances
soaPERF: nbodySOA.c
	$(CC) -Ofast -DPERF $< -o bin/$@ $(LFLAGS)
# version répertoriant la position de chaque particule à chaque temps (pour pouvoir comparer)
soaPREC: nbodySOA.c
	$(CC) -DPREC $< -o bin/$@ $(LFLAGS)


# Macro de generation de fichiers de données de performances
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
# génère l'executable qui va traiter les données
perfProcess: data/data_processing/perf_process.c
	$(CC) $< -o bin/$@
# génère le graphe des performances
plotPerf: data/data_processing/gnu_perf.gp data/data_processing/perf_process.c
	gnuplot -c $<
	eog perf.png
# généère le graphe des speedups
plotPerfSpeedup: data/data_processing/gnu_perf_speedup.gp data/data_processing/perf_process.c
	gnuplot -c $<
	eog perfSpeedup.png

# DATA PROCESSING PRECISION
# génère l'executable qui va traiter les données
precProcess: data/data_processing/prec_process.c
	$(CC) -g $< -o bin/$@
	bin/precProcess 5000 data/files/basePrec data/files/soaPrec data/files/quadPrec
# génère le graphe des précisions
plotPrec: data/data_processing/gnu_prec.gp data/data_processing/prec_process.c
	gnuplot -c $<
	eog prec.png




clean:
	rm -f bin/*
	rm -f a.out
	rm -r maqao*