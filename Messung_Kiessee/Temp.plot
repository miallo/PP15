reset
set terminal epslatex color
set output 'temp_goe.tex'

set key bottom right

set xlabel '$z$ [m]'
set ylabel '$T\, [\si{\celsius}]$'

set yrange[15:40]
set xrange[-0.2:*]
f(x)=21.185-0.430*x


p 'alle.DAT' u ($10*1.1):($2-20/3.851) w d notitle, 1/0 w p lc 1 ps 1.5 pt 7 t 'Messwerte (ohne Ausreißer)', f(x) t'Approximation' lt -1

set output
!epstopdf temp_goe.eps
!rm temp_goe.eps
