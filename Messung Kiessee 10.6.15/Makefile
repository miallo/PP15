#-----------------------------------------------------------------
QUELL=main.cpp
PROG=main
CC=g++
CFLAGS=-Wall
#-----------------------------------------------------------------
OBJECTS=$(QUELL:.cpp=.o)
all: $(PROG)
	rm -f $(PROG) *.o *.toc *.log

$PROG: $(OBJECTS)
	$(CC) $(CFLAGS) $(QUELL) -o$@

%.o: %-cpp
	$(CC) $(CFLAGS) -c $< -o $@
	. /main
          
Prohaupt. pdf: Prohaupt.tex
	p dflatex Prohaupt.tex
	p dflatex Prohaupt.tex
          
clean:    
	rm -f $(PROG) *.o *.toc *.log
          
          
          
          
          
          
