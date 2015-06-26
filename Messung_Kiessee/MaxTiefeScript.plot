reset

stats 'tiefe.dat' u 0 nooutput

set print 'maxTiefe.dat'
print '#max. Tiefe[m]'


do for [i=0:int(STATS_blocks-1)] {	
	set xrange[*:*]
	set yrange[*:*]
	
	stats 'tiefe.dat' index i u 1  nooutput
	print STATS_max
}

reset
set print
