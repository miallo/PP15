reset

set terminal epslatex color
set output 'led.tex'

set key top right

set xlabel '$x$ [m]'
set ylabel '$\ln(\Delta I)$'

set xrange[-0.2:*]

p 'supermessung.dat' u ($6*1.1):(log($9-$8)) w d t 'blaue LED',\
  'supermessung.dat' u ($6*1.1):(log($10-$8)) w d t 'IR-LED'

  
set output
!epstopdf led.eps
!rm led.eps
