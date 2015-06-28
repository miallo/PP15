reset

stats 'alle.DAT' u 0 nooutput

points = 40

set print 'records.dat'

do for [i=0:int(STATS_blocks-1)] {
	stats 'alle.DAT' index i u 0  nooutput
	records = STATS_records
	print records
}

reset
set print
