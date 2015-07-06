reset

set terminal epslatex color
set output 'led.tex'

set key top right

set xlabel '$z$ [m]'
set ylabel '$\Delta U \propto\Delta I$ [V]'

set xrange[-0.2:7.5]
set yrange[-0.02:0.03]

p 'supermessung.dat' u ($6*1.1):(($9-$8)) w p pt 7 ps 0.1 lc 3  notitle, 1/0 w p pt 7 ps 1.5 lc 3 t 'blaue LED',\
  'supermessung.dat' u ($6*1.1):(($10-$8)) w p pt 7 ps 0.1 lc 1 notitle, 1/0 w p pt 7 ps 1.5 lc 1 t 'IR-LED'

  
set output
!epstopdf led.eps
!rm led.eps
