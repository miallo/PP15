reset

stats 'supermessung.dat' u 0 nooutput

set xrange [0.5:*]

set fit quiet
set fit logfile '/dev/null'
set fit errorvariables
f(x)=a*x+b

set print 'Licht2.dat'


do for [i=0:int(STATS_blocks-1)] {		
	stats 'supermessung.dat' index i u ($6*1.1):(log($8)) nooutput
	fit f(x) 'supermessung.dat' index i u ($6*1.1):(log($8)) via a,b
	
	#print STATS_slope,STATS_intercept,STATS_correlation
	print a,a_err,b,b_err,STATS_correlation
	
	plot 'supermessung.dat' index i u ($6*1.1):(log($8)), f(x)
	pause 0.5
}

set print
