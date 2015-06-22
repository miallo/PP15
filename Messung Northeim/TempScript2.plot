reset

set print 'maxTiefe.dat'

stats 'superTemp2.dat' u 0:5 nooutput

do for [i=0:int(STATS_blocks-2)] {
	stats 'superTemp2.dat' index i u 0:5 nooutput
	print STATS_max_y
}

set print
