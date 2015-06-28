reset
set terminal epslatex color
set output 'temp_goe_bsp2.tex'

set key top right

set xlabel 'Zeit t[s]'
set ylabel '$T\, [\si{\celsius}]$'

set xrange[-0.2:*]
set yrange[15:40]


p 'alle.DAT' index 43 u ($0/100):($2-20/3.851) t '15:14 Uhr' lc 2,\

set output
!epstopdf temp_goe_bsp2.eps
!rm temp_goe_bsp2.eps
