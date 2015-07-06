reset

set terminal epslatex color
set output 'ledGoe.tex'

set key top right

set xlabel '$z$ [m]'
set ylabel '$\ln(\Delta I)$'

set xrange[-0.2:2.4]
set yrange[-0.02:0.03]

p 'alle.DAT' u ($10*1.1):(($7-$6)) w p pt 7 ps 0.1 lc 3  notitle, 1/0 w p pt 7 ps 1.5 lc 3 t 'blaue LED',\
  'alle.DAT' u ($10*1.1):(($8-$6)) w p pt 7 ps 0.1 lc 1 notitle, 1/0 w p pt 7 ps 1.5 lc 1 t 'IR-LED'

  
set output
!epstopdf ledGoe.eps
!rm ledGoe.eps
