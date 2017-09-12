#include "p4.h"

int main(int argc, char** argv){
    int sockfd,n;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len;
    char mesg[SIZE];
    int port = atoi(argv[1]);
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);
    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    
    for (;;)
    {
        len = sizeof(cliaddr);
        n = recvfrom(sockfd,mesg,SIZE,0,(struct sockaddr *)&cliaddr,&len);
        sleep(6);
        sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
        printf("Message received.\n");
    }
    
}