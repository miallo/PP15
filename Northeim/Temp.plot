reset

set terminal epslatex color
set output 'temp.tex'

set key top right


#set xrange [0.2:1.5]
#stats 'superTemp3.dat' u 5:7 name "curve1"
#f1(x)=curve1_intercept+curve1_slope*x

#set xrange [1.5:5.8]
#stats 'superTemp3.dat' u 5:7 name "curve2"
#f2(x)=curve2_intercept+curve2_slope*x


#set xrange [5.8:7.5]
#stats 'superTemp3.dat' u 5:7 name "curve3"
#f3(x)=curve3_intercept+curve3_slope*x

#f4(x)=x<1.5 ? f1(x) : f2(x)
#f(x)=x<5.8 ? f4(x) : f3(x)

c1=0.2
c2=1.5
c3=5.9
c4=7.5

f1(x)=a1*x+b1
f2(x)=a2*x+b2
f3(x)=a3*x+b3
f4(x)=x<c2 ? f1(x):f2(x)
f(x)=x<c3 ? f4(x):f3(x)

set fit quiet
set fit logfile '/dev/null'
set fit errorvariables

set xrange[c1:c4]
fit f(x) 'superTemp3.dat' u 5:7 via a1,a2,a3,b1,b2,b3

set print 'TempApprox.dat'
print c1,c2,a1,a1_err,b1+a1*c1, b1+a1*c2
print c2,c3,a2,a2_err,b2+a2*c2, b2+a2*c3
print c3,c4,a3,a3_err,b3+a3*c3, b3+a3*c4
set print


set xrange [-0.2:7.5]
set yrange [14.5:*]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'superTemp3.dat' u 5:7 w p pt 7 ps 0.2 notitle, 1/0 w p pt 7 ps 1.5 lc 1 t'bereinigte Daten',\
  f(x) lt -1 t'Approximation'
  
set output
!epstopdf temp.eps
!rm temp.eps

#=================================================

reset

set terminal epslatex color
set output 'temp_roh.tex'

set key top right

set xrange [-0.2:7.5]
set yrange [10:35]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'supermessung.dat' u ($6*1.1):3 w p pt 7 ps 0.05 lc 1 notitle, 1/0 t'Rohdaten' w p pt 7 ps 1.5 lc 1
  
set output
!epstopdf temp_roh.eps
!rm temp_roh.eps

#=================================================

reset

set terminal epslatex color
set output 'temp_tiefe.tex'

c1=0.2
c2=1.5
c3=5.9
c4=7.5

f1(x)=a1*x+b1
f2(x)=a2*x+b2
f3(x)=a3*x+b3
f4(x)=x<c2 ? f1(x):f2(x)
f(x)=x<c3 ? f4(x):f3(x)

set fit quiet
set fit logfile '/dev/null'
set fit errorvariables

set xrange[c1:c4]
fit f(x) 'superTempTiefe3.dat' u 6:7 via a1,a2,a3,b1,b2,b3

set print 'TempApprox2.dat'
print c1,c2,a1,a1_err,b1+a1*c1, b1+a1*c2
print c2,c3,a2,a2_err,b2+a2*c2, b2+a2*c3
print c3,c4,a3,a3_err,b3+a3*c3, b3+a3*c4
set print

set key top right

set xrange [-0.2:7.5]
set yrange [14.5:*]

set xlabel '$z$ [m]'
set ylabel '$T$ [$\si{\celsius}$]'

p 'superTempTiefe3.dat' u 6:7 w p pt 7 ps 0.3 notitle, 1/0 w p pt 7 ps 1.5 lc 1 t'bereinigte Daten',\
  f(x) lt -1 t'Approximation'
  
set output
!epstopdf temp_tiefe.eps
!rm temp_tiefe.eps
