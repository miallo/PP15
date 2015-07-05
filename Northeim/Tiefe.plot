reset
set terminal epslatex color
set output 'tiefe.tex'


set size ratio -1

set xlabel '$x$ [m]'
set ylabel '$y$ [m]'
set cblabel '$z$ [m]'


set key bottom right

set zrange [*:-0.5]
set grid

la(x)=x*(40000/360)
lo(x,y)=la(x)*sin(pi/2-pi/180*y)

a = 9.961131
b = 51.728028

x0 = lo(a,b)
y0 = la(b)

set pm3d map

set label "N" at -340,-1300
set arrow 3 from -300,-1500 to -300,-1350

set parametric
sp 'test.txt' u 1:2:(-$3) t 'max. Tiefe',\
   'NortheimGrosserSeeKontour.kml' u (1000*(lo($1,$2)-x0)):(1000*(la($2)-y0)):(-1) w l lt -1 notitle,\
   'NortheimGrosserSeeInsel.kml' u (1000*(lo($1,$2)-x0)):(1000*(la($2)-y0)):(-1) w l lt -1 notitle,\
   'GPSsingle_2015_06_17.txt' u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0)):(-1) w l lt 0  notitle


set output
!epstopdf tiefe.eps
!rm tiefe.eps
