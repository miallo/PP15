reset
la(x)=x*(40000/360)
lo(x,y)=la(x)*sin(pi/2-pi/180*y)

a = 9.9613
b = 51.7199

x0 = lo(a,b)
y0 = la(b)
c = 15*pi/180


set xrange [-100:100]
set yrange [-700:900]

#set size square

plot '06171518.txt' u (1000*(lo($12,$11)-x0)):(1000*(la($11)-y0)) w lp, '06171523.txt' u (1000*(lo($12,$11)-x0)):(1000*(la($11)-y0)) w lp, 'GPSkomplett_2015_06_17.txt' u (1000*(lo($2,$1)-x0)):(1000*(la($1)-y0)) w lp
