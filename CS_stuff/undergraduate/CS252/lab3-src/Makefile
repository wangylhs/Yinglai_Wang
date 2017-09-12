
#Use GNU compiler
cc = gcc
CC = -std=c99 g++ -g

LEX=lex
YACC=yacc

all: shell cat_grep ctrl-c regular

shell: shell.l shell.y command.cc
	$(LEX) shell.l
	$(YACC) -d shell.y
	$(CC) -o shell lex.yy.c y.tab.c command.cc tty-raw-mode.c read-line.c -lfl

cat_grep: cat_grep.cc
	$(CC) -o cat_grep cat_grep.cc

ctrl-c: ctrl-c.cc
	$(CC) -o ctrl-c ctrl-c.cc

regular: regular.cc
	$(CC) -o regular regular.cc 

read-line-example:
	$(CC) -o read-line-example read-line-example.c tty-raw-mode.c read-line.c
clean:
	rm -f lex.yy.c y.tab.c  y.tab.h shell ctrl-c regular cat_grep *.o read-line-example

