reset
set terminal epslatex color
set output 'temp_goe_bsp.tex'

set key top right

set xlabel '$z$ [m]'
set ylabel '$T\, [\si{\celsius}]$'

set xrange[-0.2:*]
set yrange[15:40]


p 'alle.DAT' index 25 u ($10*1.1):($2-20/3.851) t '14:34 Uhr',\
  'alle.DAT' index 43 u ($10*1.1):($2-20/3.851) t '15:14 Uhr',\

set output
!epstopdf temp_goe_bsp.eps
!rm temp_goe_bsp.eps
