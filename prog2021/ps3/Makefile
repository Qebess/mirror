CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=-lm -lcurses
OUTPUT=game

all: $(OUTPUT)

$(OUTPUT): main.c  k.c k.h hof.c hof.h ui.c ui.h
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
		gcc $(CFLAGS) main.c k.c ui.c hof.c $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o
k.o: k.c k.h
	gcc $(CFLAGS) -c k.c -o k.o
ui.o: ui.c ui.h
	gcc $(CFLAGS) -c ui.c -o ui.o
hof.o: hof.c hof.h
	gcc $(CFLAGS) -c hof.c -o hof.o
clean:
	rm -rf $(OUTPUT) *.o
