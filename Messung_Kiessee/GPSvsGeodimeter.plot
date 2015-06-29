reset
set terminal epslatex color
set output 'GPSvsGeo.tex'


set size ratio -1

set xlabel 'x [m]'
set ylabel 'y [m]'


set key bottom right

set yrange [-300:*]

la(x)=x*(40000/360)
lo(x,y)=la(x)*sin(pi/2-pi/180*y)

a = 9.920395
b = 51.520042

x0 = lo(a,b)
y0 = la(b)
c = 12*pi/180

plot 'test.txt' u (1000*(lo($1,$2)-x0)):(1000*(la($2)-y0)) t 'GPS',\
	 'Geodimeter10-6.txt' index 0 u (cos(c)*$2-sin(c)*$3):(-sin(c)*$2-cos(c)*$3) w lp t 'Geodimeter',\
	 'Kiessee.kml' u (1000*(lo($1,$2)-x0)):(1000*(la($2)-y0)) w l lt -1 notitle
	 
set output
!epstopdf GPSvsGeo.eps
!rm GPSvsGeo.eps
