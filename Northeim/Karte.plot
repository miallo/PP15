reset
set terminal epslatex color
set output 'karte.tex'

set xlabel 'x [m]'
set ylabel 'y [m]'

set grid

la(x)=x*(40000/360)
lo(x,y)=la(x)*sin(pi/2-pi/180*y)

a = 9.961131
b = 51.728028

x0 = lo(a,b)
y0 = la(b)


set xrange [-400:1000]
set yrange [-1600:200]

set size ratio -1

p 'NortheimGrosserSeeKontour.kml' u (1000*(lo($1,$2)-x0)):(1000*(la($2)-y0)) w l lt -1 t 'Seekontur',\
  'NortheimGrosserSeeInsel.kml' u (1000*(lo($1,$2)-x0)):(1000*(la($2)-y0)) w l lt -1 notitle,\
  'GPSsingle_2015_06_17.txt' u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0))  t 'Messpunkte (IPhone)',\
  #'supermessung.dat' u (1000*(lo($12,$11)-x0)):(1000*(la($11)-y0)) w lp t 'Garmin'
  
set output
!epstopdf karte.eps
!rm karte.eps
  
