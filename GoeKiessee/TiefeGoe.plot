reset
set terminal epslatex color size 15cm,8cm
set output 'tiefeGoe.tex'

set bmargin 0.0
set tmargin 0.0

set size ratio -1

set xlabel '$x$ [m]'
set ylabel '$y$ [m]'
set cblabel '$z$ [m]'


set key bottom right

set xrange [-150:*]
set zrange [*:-0.5]


la(x)=x*(40000/360)
lo(x,y)=la(x)*sin(pi/2-pi/180*y)

a = 9.920395
b = 51.520042

a = 9.920334
b = 51.520021

x0 = lo(a,b)
y0 = la(b)
c = 10*pi/180

set pm3d map

set label "N" at -90,-56
set arrow 3 from 30,-50 to -50,-50

set parametric
sp 'test.txt' u (sin(c)*$1+cos(c)*$2):(cos(c)*$1-sin(c)*$2):(-$3) t 'max. Tiefe',\
   'Kiessee.kml' u (-1000*(la($2)-y0)):(1000*(lo($1,$2)-x0)):(-1) w l lt -1 notitle,\
   'DatenKoordianten.csv' u (sin(c)*$3+cos(c)*$4):(cos(c)*$3-sin(c)*$4):(-1) w l lt 0 notitle
set output
!epstopdf tiefeGoe.eps
!rm tiefeGoe.eps
