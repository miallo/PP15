reset

set terminal pdf color solid
set output 'abs.pdf'
set grid
set title 'Absorptionskoeffizient reines Wasser, sichtbares Licht'
set ylabel 'Absorptionskoeffizient [1/m]'
set xlabel 'Wellenlänge [nm]'
plot 'abs.dat' u 1:2 t'Absorption'
set output 
set terminal wxt
replot

