reset

set terminal epslatex color
set output 'tempV1.tex'

set key top right

set xrange [-0.2:7.5]
set yrange [15.5:*]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'superTemp3.dat' index 26 u 5:7 smooth sbezier t'12:59 Uhr',\
  'superTemp3.dat' index 52 u 5:7 smooth sbezier lt -1 t'14:46 Uhr',\
  'superTemp3.dat' index 26 u 5:7 lc 1 notitle,\
  'superTemp3.dat' index 52 u 5:7 lc -1 notitle,\
  
set output
!epstopdf tempV1.eps
!rm tempV1.eps

#================================================================

reset

set terminal epslatex color
set output 'tempV2.tex'

set key top right

set xrange [-0.2:7.5]
set yrange [15.5:*]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'superTemp3.dat' index 31 u 5:7 smooth sbezier t'13:16 Uhr',\
  'superTemp3.dat' index 51 u 5:7 smooth sbezier lt -1 t'14:42 Uhr',\
  'superTemp3.dat' index 31 u 5:7 lc 1 notitle,\
  'superTemp3.dat' index 51 u 5:7 lc -1 notitle,\
  
set output
!epstopdf tempV2.eps
!rm tempV2.eps

#=================================================================

reset

set terminal epslatex color
set output 'tempV3.tex'

set key top right

set xrange [-0.2:7.5]
set yrange [15.5:*]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'superTemp3.dat' index 19 u 5:7 smooth sbezier t'12:39 Uhr',\
  'superTemp3.dat' index 54 u 5:7 smooth sbezier lt -1 t'14:53 Uhr',\
  'superTemp3.dat' index 19 u 5:7 lc 1 notitle,\
  'superTemp3.dat' index 54 u 5:7 lc -1 notitle,\
  
set output
!epstopdf tempV3.eps
!rm tempV3.eps
