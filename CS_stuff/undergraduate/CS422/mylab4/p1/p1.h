#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#define SIZE 1024
#define BLOCK 4096

char buf[BLOCK];                     //buffer used to read file
int line;                           //record how many lines does the file have
int listenfd, connfd;               //server and client file descriptor
char mesg[BLOCK];                    //buffer used to receive message from client

void sighandler(int);
int fileExist(const char*);
void readFile(char*);