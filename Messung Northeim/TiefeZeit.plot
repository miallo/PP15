reset

stats 'supermessung.dat' u 1:3

set yrange [0:8]
#set xrange [-0.5:7]


do for [i=0:int(STATS_blocks-1)] {	
#	stats 'supermessung.dat' index i u 6:3
	
	plot 'supermessung.dat' index i u 1:6
	pause 0.5
}
