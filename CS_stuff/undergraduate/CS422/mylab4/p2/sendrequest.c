#include "p2.h"

void sendrequest(char* p) {
    const char* start="letschat";       //payload of initiate message
    int n;
    sideflag = 1;
    /* set up target server */
    sock=socket(AF_INET, SOCK_DGRAM, 0);
	/* We must own the socket to receive the SIGIO message */
    if (fcntl(sock, F_SETOWN, getpid()) < 0)
    perror("Unable to set process owner to us");
	/* Arrange for nonblocking I/O and SIGIO delivery */
    if (fcntl(sock, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
    perror("Unable to put client sock into non-blocking/async mode");
    /* to avoid permission denial problem */
    int on=1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
    bzero(&target,sizeof(target));
    target.sin_family = AF_INET;
    target.sin_addr.s_addr=inet_addr(tarIP);
    target.sin_port=htons(tarport);
    
    
    /* send letschat to target peer */
    n = sendto(sock,start,strlen(start),0,(struct sockaddr *)&target,sizeof(target));
    
	sendto(sock, p, strlen(p), 0, (struct sockaddr *)&target,sizeof(target));
    /* if time out flag is true and send success, alarm arise */
    if(n>0 && timeoutflag==1){
        alarm(5);
    }
}
