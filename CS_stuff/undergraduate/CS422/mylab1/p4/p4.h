#include <time.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#define SIZE 1024
struct timeval getTime();
void sighandler(int);