
all: server client vpntunnel vpntunneld

server:
	gcc -g -o mobilereminderd server.c getTime.c readf.c sighandler.c mobilereminderd.c

client:
	gcc -g -o mobilereminder getTime.c mobilereminder.c 

vpntunnel:
	gcc -g -o vpntunnel vpntunnel.c

vpntunneld:
	gcc -g -o vpntunneld vpntunneld.c sighandler.c readf.c tostring.c sendkey.c

clean:
	rm -f mobilereminderd mobilereminder vpntunneld vpntunnel
