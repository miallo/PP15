reset

stats 'supermessung.dat' u 1:3 nooutput

set yrange [10:25]

set print 'tempavg.dat'
print '#Average Temp'

do for [i=0:int(STATS_blocks-1)] {	
	stats 'supermessung.DAT' index i u 0:3 nooutput
	print STATS_mean_y
	
	plot 'supermessung.dat' index i u 0:3
	pause 1
}
