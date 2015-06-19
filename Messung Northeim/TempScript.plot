reset

stats 'supermessung.dat' u 0:3 nooutput

#set yrange [20:45]

points = 40

set print 'superTemp3.dat'
print '#points ',points


do for [i=0:0] {	#int(STATS_blocks-1)] {	
	set xrange[*:*]
	set yrange[*:*]
	stats 'supermessung.dat' index i u 0:1 nooutput
	records = STATS_records
	
	do for [j=0:floor(records/points)]{
		set xrange[j*points:(j+1)*points-1]
		set yrange[*:*]
		
		stats 'supermessung.dat' index i u 0:3 nooutput
		
		tempmax = STATS_median_y
		set yrange [*:tempmax]
		
		stats 'supermessung.dat' index i u 0:3 nooutput
		print STATS_mean_y, STATS_stddev_y, STATS_records
		
		#plot 'supermessung.dat' index i u 0:3, STATS_mean_y
		#pause 0.5
	}
}
