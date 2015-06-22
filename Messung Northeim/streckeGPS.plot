reset
la(x)=x*(40000/360)
lo(x,y)=la(x)*sin(pi/2-pi/180*y)

a = 9.9613
b = 51.7199

x0 = lo(a,b)
y0 = la(b)
c = 15*pi/180


set xrange [-500:400]
set yrange [-500:1000]

set size ratio -1

plot 'GPSkomplett_2015_06_17.txt' u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0)) w lp, 'GPSsingle_2015_06_17.txt' u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0)) w lp
#plot 'GPSsingle_2015_06_17.txt' u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0)) w lp
