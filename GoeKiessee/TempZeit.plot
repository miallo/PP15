reset

stats 'alle.dat' u 0:2

set yrange [20:45]

set print 'tempavg.dat'
print '#Average Temp'
set print

do for [i=0:int(STATS_blocks-1)] {	
	stats 'alle.DAT' index i u 0:2
	
	set print 'tempavg.dat' append
	print STATS_mean_y
	set print
	
	plot 'alle.DAT' index i u 0:2
	pause 0.5
}
