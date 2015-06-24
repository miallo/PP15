reset

set terminal epslatex color solid
set output 'abs.tex'
set grid
set title 'Absobtionskoeffizient reins Wasser sichtbares Licht'
set ylabel '[1/cm]'
set xlabel 'lambda nm'
plot 'abs.dat' u 1:2
set output 
!epstopdf abs.eps

