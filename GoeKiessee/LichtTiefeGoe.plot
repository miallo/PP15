reset

stats 'alle.DAT' u 0 nooutput

set xrange [-0.2:2.4]

set fit quiet
#set fit logfile '/dev/null'
set fit errorvariables
f(x)=a*x+b
c=0.00313

set print 'Licht.dat'


do for [i=0:int(STATS_blocks-1)] {		
	stats 'alle.DAT' index i u ($10*1.1):(log($6-c)) nooutput
	fit f(x) 'alle.DAT' index i u ($10*1.1):(log($6-c)) via a,b
	
	#print STATS_slope,STATS_intercept,STATS_correlation
	print i,STATS_correlation,a,a_err,b,b_err
	
	#plot 'alle.DAT' index i u ($10*1.1):(log($6-c)), f(x)
	#pause 0.5
}

set print
