reset
la(x)=x*(40000/360)
lo(x,y)=la(x)*sin(pi/2-pi/180*y)

a = 9.920395
b = 51.520042

x0 = lo(a,b)
y0 = la(b)
c = 15*pi/180

plot 'GPSkomplett_2015_06_17.txt' u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0))#, 'GPSsingle_2015_06_16.txt' u (1000*(lo($3,$2)-x0)):(1000*(la($2)-y0))
