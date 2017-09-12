#include "p1c.h"
#define BLOCK 4096


int main(int argc, char** argv){
    if (argc != 5)
    {
        printf("usage: <IP address> <Port number> <file-path> <filename>\n");
        exit(1);
    }
    //variables used to build connection with server
    int sockfd,n;
    struct sockaddr_in servaddr,cliaddr;
    char recbuf[BLOCK];
    int port = atoi(argv[2]);
    const char* invalid = "INVALID REQUEST";
    //create connection
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(port);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    //send file path to server
    n = write(sockfd, argv[3], strlen(argv[3]));
    //program exit if error on write
    if(n<0){
        perror("error reading from socket");
        exit(1);
    }
    //start receiving if send succeed
    if(n==strlen(argv[3])){
        //prepare to download file
        int outfd = open(argv[4], O_WRONLY | O_CREAT, 0644);    //create file
        //write received message into file
        while((n=read(sockfd, recbuf, BLOCK))>0){
            if(strcmp(recbuf, invalid)==0){
                printf("%s\n", invalid);
                exit(0);
            }
            
            write(outfd, &recbuf, n);
            memset(recbuf,0,BLOCK);
        }
        close(outfd);
        close(sockfd);
    }
}