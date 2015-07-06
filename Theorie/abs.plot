reset

set terminal epslatex color solid
set output 'abs.tex'
set grid
set title 'Absorptionskoeffizient reines Wasser, sichtbares Licht'
set ylabel '$\alpha$ [1/cm]'
set xlabel '$\lambda$ [nm]'
plot 'abs.dat' u 1:2 t'Absorption'
set output 
!epstopdf abs.eps
!rm abs.eps

