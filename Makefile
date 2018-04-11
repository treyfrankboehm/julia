PROGRAM=julia
PARAMETERS=parameters.h
DATA=data.txt

CFLAGS=-Wall -g -lm -O2
CC=gcc

all: $(PROGRAM)
	@time ./$(PROGRAM)

gif: all
	@echo "  Creating a gif from the PNGs  "
	@time convert -delay 6 png/*.png julia.gif

$(PROGRAM): clean $(PROGRAM).c $(PARAMETERS)
	@echo "  CC    $(PROGRAM).c  "
	@$(CC) $(CFLAGS) $(PROGRAM).c -o $(PROGRAM)

clean:
	@echo "  Cleaning  "
	@rm -f $(PROGRAM) $(DATA)
	@rm -rf png

