#include "p3.h"


int main(int argc, char** argv){
    if (argc != 3)
    {
        printf("usage: <IP address> <Port number>\n");
        exit(1);
    }
    
    int sockfd,n;
    struct sockaddr_in servaddr,cliaddr;
    char sendline[SIZE];
    char recvline[SIZE];
    int port = atoi(argv[2]);
    //initialize sendline
    int i;
    for(i=0;i<SIZE;i++) sendline[i]=0;
    
    
    
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(port);
    
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    bzero(sendline, SIZE);

    
    struct timeval before = getTime();
    n = write(sockfd, sendline, SIZE);
    if(n<0){
        perror("error writing to socket");
    }
    //bzero(recvline, SIZE);
    n = read(sockfd, recvline, SIZE);
    if(n<0){
        perror("error reading from socket");
    }
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
    
    close(sockfd);
    
}

