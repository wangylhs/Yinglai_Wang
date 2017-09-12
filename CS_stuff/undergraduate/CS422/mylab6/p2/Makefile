
all: server client

server:
	gcc -g -o fsserver fsserver.c sighandler.c
client:
	javac fsclient.java

clean:
	rm -f fsserver fsclient
	rm -r *.class
