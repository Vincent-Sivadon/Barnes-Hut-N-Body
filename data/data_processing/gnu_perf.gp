set term png size 1000,600
set output 'perf.png'

set grid

set ylabel "Iteration time"
set logscale y

set xlabel "Number of bodies"

set key left top

plot 'data/files/base_mean.dat' w lp lw 2 ps 1.5 pt 6 title "Base", \
     'data/files/soa_mean.dat'  w lp lw 2 ps 1.5 pt 6 title "SOA", \
     'data/files/quad_mean.dat' w lp lw 2 ps 1.5 pt 6 title "Quad"