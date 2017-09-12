#include "p1client.h"

int main(int argc, char** argv){
    struct sigaction act;
    act.sa_handler = sighandlerc;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    if(sigaction(SIGALRM, &act, 0) == -1)
    {
        perror("sigaction");
    }
    if (argc != 4)
    {
        printf("usage: [IP address] [Port number] [secret-key]\n");
        exit(1);
    }
    keylen = strlen(argv[3]);
    ackflag=0;
    port = atoi(argv[2]);
    strcpy(key, argv[3]);
    const char* ACK = "acknowledgment";
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(port);
    struct timeval before = getTime();
    len = sizeof(servaddr);
    
    sendto(sockfd,key,keylen,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
    alarm(5);
    while(1){
        n=recvfrom(sockfd,rec,SIZE,0,(struct sockaddr *)&servaddr,&len);
        if(strncmp(rec, ACK, strlen(ACK))==0){
            ackflag=1;
        }else{
        int i;
        for(i=0;i<n;i++){
            write(2,&rec[i],1);
            if(i==(n-1)) write(2,"\n",1);
        }
        }
    }
    
}
