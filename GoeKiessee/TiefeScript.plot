reset

stats 'alle.DAT' u 0 nooutput

points = 40

set print 'tiefe.dat'
print '#points ',points
print '#Tiefe[m]'


do for [i=0:int(STATS_blocks-1)] {	
	set xrange[*:*]
	set yrange[*:*]
	
	stats 'alle.DAT' index i u 0:($10*1.1)  nooutput
	records = STATS_records
	
	if(records>1500){	
		do for [j=0:(floor(records/points)-1)]{
			set xrange[j*points:(j+1)*points-1]
			set yrange[*:*]
		
			stats 'alle.DAT' index i u 0:($10*1.1) name "tiefe" nooutput
			print tiefe_mean_y
		}
	} else {
		print STATS_max_y
	}

	print "\n"
}

reset
set print
