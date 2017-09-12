all: server client

server:
	gcc -g -o myaudiostreamd audioserver.c
client:
	gcc -g -o myaudiostream audioclient.c

clean:
	rm -f myaudiostreamd myaudiostream
