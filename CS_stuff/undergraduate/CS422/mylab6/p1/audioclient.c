#include "client.h"
#define BLOCK 1024



int main(int argc, char** argv){
    /*if(argc!=9){
        printf("usage: %myaudiostream  server-tcp-port payload-size pb-del gamma buf-sz target-buf log-file-c requested-file\n");
        exit(1);
    }*/
    //create tcp connection
    int tcp_sockfd,n;
    struct sockaddr_in tcp_servaddr,tcp_cliaddr;
    char recbuf[BLOCK];
    int port = atoi(argv[2]);
    tcp_sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&tcp_servaddr,sizeof(tcp_servaddr));
    tcp_servaddr.sin_family = AF_INET;
    tcp_servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    tcp_servaddr.sin_port=htons(port);
    connect(tcp_sockfd, (struct sockaddr *)&tcp_servaddr, sizeof(tcp_servaddr));
    n = write(tcp_sockfd, argv[3], strlen(argv[3]));
    memset(recbuf,0,BLOCK);
    
    //create udp
    int udp_sock;
    struct sockaddr_in udp_servaddr,udp_cliaddr;
    socklen_t udp_clilen;
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    udp_servaddr.sin_family = AF_INET;
    udp_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    udp_servaddr.sin_port = htons(50023);
    if(bind(udp_sock,(struct sockaddr *)&udp_servaddr,sizeof(udp_servaddr)) < 0){
        perror("udp bind() failed");
        //exit(1);
    }
    
    udp_clilen = sizeof(udp_servaddr);
    while((n=recvfrom(udp_sock, recbuf, BLOCK, 0, (struct sockaddr *) &udp_servaddr, &udp_clilen))>0){
        printf("%s\n", recbuf);
        
        memset(recbuf,0,BLOCK);
    }
    /*
    while((n=read(tcp_sockfd, recbuf, BLOCK))>0){
        
        printf("%s\n", recbuf);
        
        memset(recbuf,0,BLOCK);
    }
     */
    close(tcp_sockfd);
}