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
#include <termios.h>
#include <arpa/inet.h>

void iohandler(int);
void alrmhandler(int);
void sendrequest(char*);

struct sockaddr_in target;
struct sockaddr_in cliaddr;         /* Address of datagram source */
unsigned int clilen;                /* Address length */
int recvMsgSize;                    /* Size of datagram */
char recvbuf[1024];                 /* Datagram buffer */

char* serverIP;
int serverport;
char *sourceIP;
int sourceport;
int chatting;
int sock;       //global socket for sighandler
int sock2;
int timeoutflag;
char tarIP[200];
int tarport;
int sideflag;
char str[200];



