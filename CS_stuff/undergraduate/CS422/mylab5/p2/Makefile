
all: server client

server:
	gcc -g -o fsserver fsserver.c sighandler.c
client:
	gcc -g -o fsclient fsclient.c

clean:
	rm -f fsserver fsclient
