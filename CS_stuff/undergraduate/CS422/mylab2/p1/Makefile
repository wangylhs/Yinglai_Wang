
all: server client

server:
	gcc -g -o mobilereminderd server.c getTime.c readf.c sighandler.c mobilereminderd.c

client:
	gcc -g -o mobilereminder getTime.c mobilereminder.c 

clean:
	rm -f mobilereminderd mobilereminder
