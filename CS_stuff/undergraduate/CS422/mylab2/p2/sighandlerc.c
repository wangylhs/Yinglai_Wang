#include "p1client.h"

void sighandlerc(int sig){
    if(ackflag==1){
        return;
    }else{
        printf("resend key.......");
        sendto(sockfd,key,keylen,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
    }
    alarm(5);
}