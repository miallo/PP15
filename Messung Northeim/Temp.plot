reset

set terminal epslatex color
set output 'temp.tex'

set key top right

set xrange [-0.2:7.5]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'superTemp3.dat' u 5:7 w d t'bereinigte Daten'
  
set output
!epstopdf temp.eps
!rm temp.eps

#=================================================

reset

set terminal epslatex color
set output 'temp_roh.tex'

set key top right

set xrange [-0.2:7.5]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'supermessung.dat' u ($6*1.1):3 w p pt 7 ps 0.05 t'Rohdaten'
  
set output
!epstopdf temp_roh.eps
!rm temp_roh.eps

#=================================================

reset

set terminal epslatex color
set output 'temp_tiefe.tex'

set key top right

set xrange [-0.2:7.5]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'superTempTiefe3.dat' u 6:7 w d t'Rohdaten'
  
set output
!epstopdf temp_tiefe.eps
!rm temp_tiefe.eps
