set term png size 1900,1000
set output 'precision_quad.png'

set grid

set ylabel "Delta"
set logscale y


set xlabel "n"

plot 'deltas.dat' title "Delta"