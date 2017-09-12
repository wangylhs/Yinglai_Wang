chess.so: chess.cpp
	g++ -o $@ -Wall -shared -g -O0 -D_GNU_SOURCE -fPIC -ldl $^
runner: runner.c
	mpicc -o runner runner.c
sample2: sample2.c
	gcc -o sample2 -lpthread -lrt sample2.c

clean:
	rm -f chess.so sample2 runner *.o *.txt
