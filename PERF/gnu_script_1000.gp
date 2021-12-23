set term png size 1900,1000
set output 'perf_1000.png'

set grid

set ylabel "Times"


set xlabel "Simulation iteration"

plot '1000_0.dat' w lp title "Basic Code", '1000_quad.dat' w lp title "Barnes-Hut"