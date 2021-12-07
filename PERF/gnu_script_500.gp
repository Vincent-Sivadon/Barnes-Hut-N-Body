set term png size 1900,1000
set output 'perf_500.png'

set grid

set ylabel "Latency in cycles"
set logscale y


set xlabel "Simulation iteration"

plot '500_0.dat' w lp title "Basic Code", '500_quad.dat' w lp title "Barnes-Hut"