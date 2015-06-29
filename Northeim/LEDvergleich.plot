reset

set terminal epslatex color
set output 'led.tex'

set key top right

set xlabel '$z$ [m]'
set ylabel '$\ln(\Delta I)$'

set xrange[-0.2:7.5]

p 'supermessung.dat' u ($6*1.1):(log($9-$8)) w p pt 7 ps 0.1 lc 3  notitle, 1/0 w p pt 7 ps 1.5 lc 3 t 'blaue LED',\
  'supermessung.dat' u ($6*1.1):(log($10-$8)) w p pt 7 ps 0.1 lc 1 notitle, 1/0 w p pt 7 ps 1.5 lc 1 t 'IR-LED'

  
set output
!epstopdf led.eps
!rm led.eps
