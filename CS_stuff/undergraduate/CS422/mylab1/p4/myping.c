#include "p4.h"


int main(int argc, char** argv){
    
    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    if(sigaction(SIGALRM, &act, 0) == -1)
    {
        perror("sigaction");
    }

    
    int port = atoi(argv[2]);
    int sockfd,n;
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
    sendto(sockfd,sendline,SIZE,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
    alarm(5);
    n=recvfrom(sockfd,recvline,SIZE,0,NULL,NULL);
    if(n==SIZE){
        struct timeval after = getTime();
        int ms;
        ms=(after.tv_usec-before.tv_usec)/1000;
        int sec = after.tv_sec-before.tv_sec;
        int ping = sec*1000+ms;
        printf("ping: %dms\n", ping);
        printf("Server IP: %d.%d.%d.%d\n",
               (int)(servaddr.sin_addr.s_addr&0xFF),
               (int)((servaddr.sin_addr.s_addr&0xFF00)>>8),
               (int)((servaddr.sin_addr.s_addr&0xFF0000)>>16),
               (int)((servaddr.sin_addr.s_addr&0xFF000000)>>24));
        printf("port: %d\n",ntohs(servaddr.sin_port));
    }
    
}