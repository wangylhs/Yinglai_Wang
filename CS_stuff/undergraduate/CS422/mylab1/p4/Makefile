
all: myping

myping:
	gcc -g -o myping getTime.c sighandler.c myping.c
	gcc -g -o mypingd mypingd.c

clean:
	rm -f myping mypingd *.o
