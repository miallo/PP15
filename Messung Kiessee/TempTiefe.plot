reset

stats 'alle.dat' u 0:2

set yrange [20:45]

do for [i=0:int(STATS_blocks-1)] {		
	plot 'alle.DAT' index i u 10:2
	pause 0.5
}