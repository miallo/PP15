reset

set terminal epslatex color
set output 'l1.tex'

set key top right

set xrange [-0.2:7.5]

set xlabel '$z$ [m]'
set ylabel '$\ln{I}$'

set fit quiet
set fit logfile '/dev/null'
set fit errorvariables

f1(x)=a1*x+b1
f2(x)=a2*x+b2
f3(x)=a3*x+b3

fit f1(x) 'supermessung.dat' index 6 u ($6*1.1):(log($8)) via a1,b1
fit f2(x) 'supermessung.dat' index 52 u ($6*1.1):(log($8)) via a2,b2
fit f3(x) 'supermessung.dat' index 60 u ($6*1.1):(log($8)) via a3,b3

p 'supermessung.dat' index 6 u ($6*1.1):(log($8)) w d t "$r=-0.96$, $a=-0.773	\pm 0.004$",\
  'supermessung.dat' index 52 u ($6*1.1):(log($8)) w d t "$r=-0.96$, $a=-0.501	\pm 0.003$",\
  'supermessung.dat' index 60 u ($6*1.1):(log($8)) w d t "$r=-0.93$, $a=-0.524	\pm 0.004$",\
  f1(x) notitle,f2(x) notitle,f3(x) notitle
  
set output
!epstopdf l1.eps
!rm l1.eps


#===============================================================================================

reset

set terminal epslatex color
set output 'l2.tex'

set key top right

set xrange [-0.2:7.5]

set xlabel '$z$ [m]'
set ylabel '$\ln{I}$'

p 'supermessung.dat' index 26 u ($6*1.1):(log($8)) w d t "$r=-0.05$",\
  'supermessung.dat' index 38 u ($6*1.1):(log($8)) w d t "$r=-0.59$",\
  
set output
!epstopdf l2.eps
!rm l2.eps
