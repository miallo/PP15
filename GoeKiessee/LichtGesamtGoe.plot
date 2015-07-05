reset

set terminal epslatex color
set output 'lichtGoe.tex'

set key top right

set xlabel '$z$ [m]'
set ylabel '$\ln{I}$'


#f(x)=-1-2*x
f(x)=-0.8-2.4*x

set xrange[-0.2:2.4]

p 'alle.DAT' u ($10*1.1):(log($6)) w p pt 7 ps 0.1 lc 1 notitle, 1/0 w p pt 7 ps 1.5 lc 1 t 'Messwerte', f(x) lt -1 t'Grenzgerade'
  
set output
!epstopdf lichtGoe.eps
!rm lichtGoe.eps
