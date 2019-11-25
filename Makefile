CFLAGS = -pedantic -Wall -Wextra -std=c99
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
PROGRAMS = ifj2019

all: ifj2019

ifj2019: $(OBJECTS)
	gcc $(CFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@

clean:
	rm *.o $(PROGRAMS)
