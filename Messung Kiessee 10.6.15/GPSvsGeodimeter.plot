reset
la(x)=x*(40000/360)
lo(x,y)=la(x)*sin(pi/2-pi/180*y)

a = 9.920395
b = 51.520042

x0 = lo(a,b)
y0 = la(b)
c = 15*pi/180

plot 'test.txt' u (1000*(lo($1,$2)-x0)):(1000*(la($2)-y0)), 'Geodimeter10-6.txt' index 0 u (cos(c)*$2-sin(c)*$3):(-sin(c)*$2-cos(c)*$3) w l
