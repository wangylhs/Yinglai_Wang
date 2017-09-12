chess.so: chess.cpp
	g++ -o $@ -Wall -shared -g -O0 -D_GNU_SOURCE -fPIC -ldl $^
run: run.c
	g++ -o run run.c
sample2: sample2.c
	gcc -o sample2 -lpthread -lrt sample2.c
