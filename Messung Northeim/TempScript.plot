reset

min(x,y) = (x < y) ? x : y

stats 'supermessung.dat' u 0:3 nooutput

#set yrange [20:45]

points = 40

set print 'superTemp.dat'
print '#points ',points


do for [i=0:int(STATS_blocks-1)] {	
	set xrange[*:*]
	set yrange[*:*]
	stats 'supermessung.dat' index i u 0:1
	stats 'supermessung.dat' index i u 0:11 name "lat" nooutput
	stats 'supermessung.dat' index i u 0:12 name "long" nooutput
	records = STATS_records
	
	do for [j=0:floor(records/points)]{
		set xrange[j*points:(j+1)*points-1]
		set yrange[*:*]
		
		stats 'supermessung.dat' index i u 0:1 name "time" nooutput
		stats 'supermessung.dat' index i u 0:4 name "ADCdruck" nooutput
		
		stats 'supermessung.dat' index i u 0:3 name "temp" nooutput
		
		tempmin = temp_lo_quartile_y - 3
		tempmax = min(temp_median_y,temp_lo_quartile_y+2)
		set yrange [tempmin:tempmax]
		
		stats 'supermessung.dat' index i u 0:3 name "temp2" nooutput
		print time_mean_y, lat_mean_y, long_mean_y, ADCdruck_mean_y ,temp2_mean_y, temp2_stddev_y, temp2_records
		
		#plot 'supermessung.dat' index i u 0:3, STATS_mean_y
		#pause 0.5
	}
	print "\n"
}

reset
set print