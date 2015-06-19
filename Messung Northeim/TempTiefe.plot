reset

stats 'supermessung.dat' u 1:3

set yrange [15:25]
set xrange [-0.5:7]

set print 'tempavg.dat'
print '#Average Temp'
set print

do for [i=0:int(STATS_blocks-1)] {	
	stats 'supermessung.dat' index i u 6:3
	
	set print 'tempavg.dat' append
	print STATS_mean_y
	set print
	
	plot 'supermessung.dat' index i u 6:3
	pause 0.5
}
