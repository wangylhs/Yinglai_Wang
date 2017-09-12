CC=gcc
CFLAGS=-std=c99

all: order_book
order_book: market.h
	$(CC) $(CFLAGS) -o order_book order_book.c market.h -lpthread -L. -lmarket64

clean:
	rm -f order_book *.o
