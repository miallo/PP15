reset

min(x,y) = (x < y) ? x : y

stats 'supermessung.dat' u 0:3 nooutput

#set yrange [20:45]

binsize = 0.05 #meter
minPoints = 30

set print 'superTempTiefe.dat'
print '#bin size ',binsize
print '#lat long maxTiefe tiefe temp temp_stdev temp_records'


do for [i=0:int(STATS_blocks-1)] {	
	set xrange[*:*]
	set yrange[*:*]

	stats 'superTemp3.dat' index i u 5 name "maxTiefe" nooutput
	TiefeMax = maxTiefe_max
	TiefeMin = -0.1	

	
	set yrange[51.71:51.74]	
	stats 'supermessung.dat' index i u 11 name "lat" nooutput
	
	set yrange[9.94:9.98]	
	stats 'supermessung.dat' index i u 12 name "long" nooutput
	
	do for [j=floor(TiefeMin/binsize):floor(TiefeMax/binsize)+1]{
		set yrange[j*binsize:(j+1)*binsize]
		stats 'supermessung.dat' index i u ($6*1.1) name "points" nooutput
		
		if(points_records >= minPoints) {
			set xrange[j*binsize:(j+1)*binsize]
			set yrange[*:*]
			
			tiefe = (2*j+1)/2.0*binsize
			stats 'supermessung.dat' index i u ($6*1.1):3 name "temp" nooutput
			
			tempmin = temp_lo_quartile_y - 3
			tempmax = min(temp_median_y-0.01,temp_lo_quartile_y+2)
			set yrange [tempmin:tempmax]
			
			stats 'supermessung.dat' index i u ($6*1.1):3 name "temp2" nooutput
			print lat_mean, long_mean, TiefeMax, tiefe, temp2_mean_y, temp2_stddev_y, temp_records, temp2_records
			
			#set yrange[16:21]		
			#plot 'supermessung.dat' index i u ($6*1.1):3, temp2_mean_y, tempmax
			#pause 0.5
		}
	}
	print "\n"
}

reset
set print
