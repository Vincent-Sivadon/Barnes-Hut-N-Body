set term png size 1000,600
set output 'prec.png'

set grid

set ylabel "Simulation iteration"
#set logscale y

set xlabel "Position mean"

set key left top

plot 'data/files/prec1.dat' u 1:2 w lp lw 2 pt 6 ps 0.5 title 'deltas soa', \
     'data/files/prec2.dat' u 1:2 w lp lw 2 pt 6 ps 0.5 title 'deltas quad'