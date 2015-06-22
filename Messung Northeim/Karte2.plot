reset
set terminal epslatex color
set output 'karte2.tex'

set key outside right center box

set xlabel 'x [m]'
set ylabel 'y [m]'


la(x)=x*(40000/360)
lo(x,y)=la(x)*sin(pi/2-pi/180*y)

a = 9.961131
b = 51.728028

x0 = lo(a,b)
y0 = la(b)


set xrange [0:400]
set yrange [-800:-250]

set size ratio -1

p 'superTemp.dat' index 26 u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0)) t'12:59 Uhr',\
  'superTemp.dat' index 52 u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0)) t'14:46 Uhr',\
  'superTemp.dat' index 31 u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0)) t'13:16 Uhr',\
  'superTemp.dat' index 51 u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0)) t'14:42 Uhr',\
  'superTemp.dat' index 19 u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0)) t'12:39 Uhr',\
  'superTemp.dat' index 54 u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0)) t'14:53 Uhr',\
  'NortheimGrosserSeeKontour.kml' u (1000*(lo($1,$2)-x0)):(1000*(la($2)-y0)) w l lt -1 notitle,\
  'NortheimGrosserSeeInsel.kml' u (1000*(lo($1,$2)-x0)):(1000*(la($2)-y0)) w l lt -1 notitle,\
  #'GPSsingle_2015_06_17.txt' u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0))  t 'IPhone',\
  #'supermessung.dat' u (1000*(lo($12,$11)-x0)):(1000*(la($11)-y0)) w lp t 'Garmin'
  
set output
!epstopdf karte2.eps
!rm karte2.eps
  
set terminal windows
replot