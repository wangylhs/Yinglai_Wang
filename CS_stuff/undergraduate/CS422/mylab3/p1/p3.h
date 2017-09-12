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

#include<signal.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<netinet/ip_icmp.h>
#include<netdb.h>
#include<setjmp.h>

//#define SIZE 1024
struct timeval getTime();
void sighandler(int);

