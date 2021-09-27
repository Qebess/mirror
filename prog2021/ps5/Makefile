CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wconversion -g
LDLIBS=-lm
OUTPUT=adventure


all: $(OUTPUT)

$(OUTPUT):
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) main.c backpack.c command.c container.c game.c item.c parser.c room.c world.c $(LDLIBS) -o $(OUTPUT)

clean:
	rm -rf $(OUTPUT) *.o
