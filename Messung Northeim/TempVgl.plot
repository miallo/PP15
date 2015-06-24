reset

set terminal epslatex color
set output 'tempV1.tex'

set key top right

set xrange [-0.2:7.5]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'superTempTiefe3.dat' index 26 u 6:7:8 w e t'12:59 Uhr',\
  'superTempTiefe3.dat' index 52 u 6:7:8 w e t'14:46 Uhr',\
  
set output
!epstopdf tempV1.eps
!rm tempV1.eps

#================================================================

reset

set terminal epslatex color
set output 'tempV2.tex'

set key top right

set xrange [-0.2:7.5]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'superTempTiefe3.dat' index 31 u 6:7:8 w e t'13:16 Uhr',\
  'superTempTiefe3.dat' index 51 u 6:7:8 w e t'14:42 Uhr',\
  
set output
!epstopdf tempV2.eps
!rm tempV2.eps

#=================================================================

reset

set terminal epslatex color
set output 'tempV3.tex'

set key top right

set xrange [-0.2:7.5]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'superTempTiefe3.dat' index 19 u 6:7:8 w e t'12:39 Uhr',\
  'superTempTiefe3.dat' index 54 u 6:7:8 w e t'14:53 Uhr',\
  
set output
!epstopdf tempV3.eps
!rm tempV3.eps