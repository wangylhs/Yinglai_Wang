CC=gcc
CFLAGS=-std=c99 -m32 -O0

all: badguy1 badguy2 overflow

overflow: vulnerable.o overflow.o overflow.c vulnerable.c
	$(CC) $(CFLAGS) -o overflow overflow.o vulnerable.o

overflow.o: overflow.c 
	$(CC) $(CFLAGS) -c overflow.c

badguy2: badguy2.o callstack.o badguy2.c callstack.c
	$(CC) $(CFLAGS) -o badguy2 badguy2.o callstack.o -L. -ltweetIt -lcurl -lssl

badguy2.o: badguy2.c
	$(CC) $(CFLAGS) -c badguy2.c

badguy1: badguy1.o callstack.o badguy1.c callstack.c
	$(CC) $(CFLAGS) -o badguy1 badguy1.o callstack.o -L. -ltweetIt -lcurl -lssl

badguy1.o: badguy1.c
	$(CC) $(CFLAGS) -c badguy1.c

callstack.o: callstack.c
	$(CC) $(CFLAGS) -c callstack.c

clean:
	rm -f badguy1 badguy2 overflow *.o
