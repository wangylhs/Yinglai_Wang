
all: myping

myping:
	gcc -g -o myping getTime.c myping.c
	gcc -g -o mypingd sighandler.c mypingd.c

clean:
	rm -f myping mypingd *.o
