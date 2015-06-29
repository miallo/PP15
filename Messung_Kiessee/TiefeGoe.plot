reset
set terminal epslatex color
set output 'tiefeGoe.tex'


set view equal xy

set xlabel 'x [m]'
set ylabel 'y [m]'
set zlabel 'z [m]'


set key bottom right

#set yrange [-300:*]

la(x)=x*(40000/360)
lo(x,y)=la(x)*sin(pi/2-pi/180*y)

a = 9.920395
b = 51.520042

x0 = lo(a,b)
y0 = la(b)
c = 12*pi/180

set hidden3d

sp 'Kiessee.kml' u (1000*(lo($1,$2)-x0)):(1000*(la($2)-y0)):(0) w l lt -1 notitle,\
  'DatenKoordianten.csv' u (cos(c)*$3-sin(c)*$4+8):(-sin(c)*$3-cos(c)*$4):(-$8) w lp t 'max. Tiefe'

set output
!epstopdf tiefeGoe.eps
!rm tiefeGoe.eps
