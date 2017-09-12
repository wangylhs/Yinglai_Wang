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
#define SIZE 1024
struct timeval getTime();
void sighandler(int);

int sockfd,n;
struct sockaddr_in servaddr,cliaddr;
socklen_t len;
char mesg[SIZE];
int port;