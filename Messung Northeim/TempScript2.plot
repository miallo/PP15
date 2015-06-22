reset

set print 'maxTiefe.dat'

stats 'superTemp.dat' u 0:5 nooutput

do for [i=0:int(STATS_blocks-1)] {
	stats 'superTemp2.dat' index i u 0:5 nooutput
	print STATS_max_y
}

set print
