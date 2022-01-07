set term png size 1000,600
set output 'perfSpeedup.png'

set grid

set ylabel "Iteration time"
set logscale y

set xlabel "Number of bodies"

set key left top

plot 'files/oct_speedup.dat' w lp lw 2 ps 1.5 pt 6 title "Octree Speedup", \
     'files/soa_speedup.dat'  w lp lw 2 ps 1.5 pt 6 title "SOA Speedup", \
