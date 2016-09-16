CFLAGS=-Wall -g -lm
CC=gcc

all: clean julia

julia: julia.c
	$(CC) $(CFLAGS) julia.c -o julia
	./julia.gplot

clean:
	rm -f *.png
	rm -f *.dat
	rm -f julia
