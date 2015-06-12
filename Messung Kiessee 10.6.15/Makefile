#-----------------------------------------------------------------
QUELL=main.cpp
PROG=main
CC=g++
CFLAGS=-Wall
#-----------------------------------------------------------------
OBJECTS=$(QUELL:.cpp=.o)
all: $(PROG)

$PROG: $(OBJECTS)
	$(CC) $(CFLAGS) $(QUELL) -o$@

%.o: %-cpp
	$(CC) $(CFLAGS) -c $< -o $@
	./main

Prohaupt.pdf: Prohaupt.tex
	pdflatex Prohaupt.tex
	pdflatex Prohaupt.tex

clean: 
	rm -f $(PROG) *.o *.toc *.log
