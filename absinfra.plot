reset

set terminal epslatex color solid
set output 'absinfra.tex'
set grid
set title 'Absobtionskoeffizient reins Wasser, infraroter Bereich'
set ylabel '[1/cm]'
set xlabel 'lambda nm'
plot 'abs.dat' u 1:2
set output 
!epstopdf absinfra.eps

