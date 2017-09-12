CC=gcc
CFLAGS=-std=c99 -O2 -g
all: memory perf

memory: memory.o
	$(CC) $(CFLAGS) -o memory memory.o
perf: perf.o
	$(CC) $(CFLAGS) -o perf perf.o
memory.o: memory.c
	$(CC) $(CFLAGS) -c memory.c
perf.o: perf.c
	$(CC) $(CFLAGS) -c perf.c
clean: 
	rm -f memory perf *.o
