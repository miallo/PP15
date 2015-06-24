reset

set terminal epslatex color
set output 'licht.tex'

set key top right

set xlabel '$z$ [m]'
set ylabel '$\ln{I}$'

#f(x)=-1.4-0.42*x
f(x)=-1.55-0.4*x

set xrange[-0.2:7.5]

p 'supermessung.dat' u ($6*1.1):(log($8)) w d t 'Messwerte', f(x) lt -1 t'Grenzgerade'
  
set output
!epstopdf licht.eps
!rm licht.eps
