reset

min(x,y) = (x < y) ? x : y

stats 'supermessung.dat' u 0:3 nooutput

#set yrange [20:45]

points = 40

set print 'superTemp3.dat'
print '#points ',points
print '#t[s] lat long tiefe tiefe_stddev temp temp_stdev temp_records'


do for [i=0:int(STATS_blocks-1)] {	
	set xrange[*:*]
	set yrange[*:*]
	stats 'supermessung.dat' index i u 0:1  nooutput
	records = STATS_records

	stats 'superTemp2.dat' index i u 0:5 name "maxTiefe" nooutput
	TiefeMax = (maxTiefe_max_y*3.3/4095*1001-1024)/100*1.1

	
	set yrange[51.71:51.74]	
	stats 'supermessung.dat' index i u 0:11 name "lat" nooutput
	
	set yrange[9.94:9.98]	
	stats 'supermessung.dat' index i u 0:12 name "long" nooutput
	
	do for [j=0:(floor(records/points)-1)]{
		set xrange[j*points:(j+1)*points-1]
		set yrange[*:*]
		
		stats 'supermessung.dat' index i u 0:($1/1000) name "time" nooutput
		
		#set yrange[1240:2150]
		stats 'supermessung.dat' index i u 0:($6*1.1) name "tiefe" nooutput
		#set yrange[*:*]

		if(tiefe_mean_y >= -0.25){		
			stats 'supermessung.dat' index i u 0:3 name "temp" nooutput
		
			tempmin = temp_lo_quartile_y - 3
			tempmax = min(temp_median_y-0.01,temp_lo_quartile_y+2)
			set yrange [tempmin:tempmax];\
		
			stats 'supermessung.dat' index i u 0:3 name "temp2" nooutput
			print time_mean_y, lat_mean_y, long_mean_y, TiefeMax, tiefe_mean_y, tiefe_stddev_y, temp2_mean_y, temp2_stddev_y, temp2_records
		
			#set yrange[16:21]		
			#plot 'supermessung.dat' index i u 0:3, temp2_mean_y, tempmax
			#pause 0.5
		}
	}
	print "\n"
}

reset
set print
