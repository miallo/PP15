reset

set terminal epslatex color
set output 'tempAlg1.tex'

min(x,y) = (x < y) ? x : y
points = 40

set key top left

i=30
a=1200

set xrange[a:a+points-1]
stats 'supermessung.dat' index i u 0:3 name "temp" nooutput

tempmin = temp_lo_quartile_y - 3
tempmax = min(temp_median_y-0.01,temp_lo_quartile_y+2)
set yrange [tempmin:tempmax];\

stats 'supermessung.dat' index i u 0:3 name "temp2" nooutput

set yrange[*:*]		
plot 'supermessung.dat' index i u 0:3 t 'Rohdaten', tempmin t '$T_{min}$',\
    tempmax t '$T_{max}$ (Median)',temp2_mean_y lt -1 t'Approximation'
	
set output
!epstopdf tempAlg1.eps
!rm tempAlg1.eps

#=============================================================================

reset

set terminal epslatex color
set output 'tempAlg2.tex'

min(x,y) = (x < y) ? x : y
points = 40

set key bottom right

i=17
a=3600

set xrange[a:a+points-1]
stats 'supermessung.dat' index i u 0:3 name "temp" nooutput

tempmin = temp_lo_quartile_y - 3
tempmax = min(temp_median_y-0.01,temp_lo_quartile_y+2)
set yrange [tempmin:tempmax];\

stats 'supermessung.dat' index i u 0:3 name "temp2" nooutput

set yrange[*:*]		
plot 'supermessung.dat' index i u 0:3 t 'Rohdaten', tempmin t '$T_{min}$',\
    tempmax t '$T_{max}$ (Median)',temp2_mean_y lt -1 t'Approximation'
	
set output
!epstopdf tempAlg2.eps
!rm tempAlg2.eps

