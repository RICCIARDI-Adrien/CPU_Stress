CC = gcc
CCFLAGS = -W -Wall -O3

BINARY = cpu-stress
SOURCES = Main.c

all:
	$(CC) $(CCFLAGS) $(SOURCES) -o $(BINARY)

clean:
	rm -f $(BINARY)
