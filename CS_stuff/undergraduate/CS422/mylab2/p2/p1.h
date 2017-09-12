#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <strings.h>
#define SIZE 1024
//func
struct timeval getTime();
void readf(int, char*);
void sighandler(int);
void server(char*);
//variables for read and signal
char buf[200][256];
int delay[200];
int inFile;
int line;
int count;
//variables for create server
int sockfd,n;
struct sockaddr_in servaddr,cliaddr;
socklen_t len;
int port;
char mesg[SIZE];
