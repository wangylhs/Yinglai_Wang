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

struct timeval getTime();
void sighandlerc(int);

int ackflag;
int port;
int sockfd,n,len;
struct sockaddr_in servaddr,cliaddr;
char key[SIZE];
char rec[SIZE];
int keylen;
