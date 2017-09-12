#include "p3.h"


int main(int argc, char** argv){
    int port = atoi(argv[2]);
    int sockfd,n,len;
    struct sockaddr_in servaddr,cliaddr;
    char sendline[SIZE];
    int i;
    for(i=0;i<SIZE;i++) sendline[i]='0';
    char recvline[SIZE];
    
    if (argc != 3)
    {
        printf("usage: <IP address> <Port number>\n");
        exit(1);
    }
    
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(port);
    struct timeval before = getTime();
    len = sizeof(servaddr);
    sendto(sockfd,sendline,SIZE,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
    n=recvfrom(sockfd,recvline,SIZE,0,(struct sockaddr *)&servaddr,&len);
    if(n==SIZE){
        struct timeval after = getTime();
        int ms;
        ms=(after.tv_usec-before.tv_usec)/1000;
        int decimal = (after.tv_usec-before.tv_usec)%1000;
        int sec = after.tv_sec-before.tv_sec;
        
        printf("ping: %d.%dms\n", (sec*1000+ms), decimal);
        printf("Server IP: %d.%d.%d.%d\n",
               (int)(servaddr.sin_addr.s_addr&0xFF),
               (int)((servaddr.sin_addr.s_addr&0xFF00)>>8),
               (int)((servaddr.sin_addr.s_addr&0xFF0000)>>16),
               (int)((servaddr.sin_addr.s_addr&0xFF000000)>>24));
        printf("port: %d\n",ntohs(servaddr.sin_port));
    }
    //recvline[n]=0;
    //fputs(recvline,stdout);
    
}