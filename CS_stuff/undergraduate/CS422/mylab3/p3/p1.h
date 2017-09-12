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
#include <arpa/inet.h>
#define SIZE 1024
//func
struct timeval getTime();
void readf(int, char*);
void sighandler(int);
void server(char*);
void tostring(char*, int);
void sendkey();
void forward();
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


int vpnport1;
int vpnport2;
int serverPort;
char* serverIP;

int sockfd2;
int sockfdc;
int sockfds;
struct sockaddr_in mobcli;
struct sockaddr_in realserver;
char receiv[SIZE];
int mobport;
char ip1[5],ip2[5],ip3[5],ip4[5];
char* mobilIP;

int temps;
