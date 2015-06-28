reset
set terminal epslatex color
set output 'temp_goe.tex'

set key bottom left

set xlabel '$z$ [m]'
set ylabel '$T\, [\si{\celsius}]$'

set yrange[15:40]

f(x)=21.185-0.430*x


p 'alle.DAT' u ($10*1.1):($2-20/3.851) t 'Messwerte (ohne Ausreißer)' w d, f(x) t'Approximation' lt -1

set output
!epstopdf temp_goe.eps
!rm temp_goe.eps
