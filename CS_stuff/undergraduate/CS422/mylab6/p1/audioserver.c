#include "server.h"
#define BLOCK 1024

int main(int argc, char** argv){
    /*
    if(argc!=7){
        printf("usage: %myaudiostreamd tcp-port udp-port payload-size packet-spacing mode log-file-s \n");
        exit(1);
    }
    */
    //buffer
    char mesg[BLOCK];
    int n;
    const char* invalid = "file does not exist or not readable.";

    
    //create TCP server
    int tcp_port = atoi(argv[1]);
    struct sockaddr_in tcp_servaddr, tcp_cliaddr;
    socklen_t tcp_clilen;
    pid_t pid;
    int listenfd, connfd;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&tcp_servaddr, sizeof(tcp_servaddr));
    tcp_servaddr.sin_family = AF_INET;
    tcp_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    tcp_servaddr.sin_port = htons(tcp_port);
    if(bind(listenfd,(struct sockaddr *)&tcp_servaddr,sizeof(tcp_servaddr)) < 0){
        perror("error on binding");
        exit(1);
    }
    listen(listenfd, 5);
    tcp_clilen = sizeof(tcp_cliaddr);
    while(1){
        //build connection
        connfd = accept(listenfd, (struct sockaddr *)&tcp_cliaddr, &tcp_clilen);
        
        //receive request from client
        memset(mesg, 0, BLOCK);
        n = read(connfd, mesg, BLOCK);
        //check file existence, check read access
        int val1, val2;
        val1 = access(mesg, F_OK);
        val2 = access(mesg, R_OK);
        if(val1==0 && val2==0){
            //file exist and readable, then create child process
            pid = fork();
            if(pid==0){
                //child process
                close(listenfd);
                close(connfd);
                fprintf(stderr, "child process begin...\n");
                //create UDP server
                int udp_sock;
                int udp_port = atoi(argv[2]);
                struct sockaddr_in udp_servaddr, udp_cliaddr;
                socklen_t udp_clilen;
                udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
                udp_servaddr.sin_family = AF_INET;
                udp_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
                udp_servaddr.sin_port = htons(udp_port);
                if(bind(udp_sock,(struct sockaddr *)&udp_servaddr,sizeof(udp_servaddr)) < 0){
                    perror("udp bind() failed");
                    exit(1);
                }
                sendto(udp_sock, "OK", strlen("OK"), 0, (struct sockaddr *)&tcp_cliaddr, sizeof(tcp_cliaddr));
                exit(0);

            }else{
                //parent process
                close(connfd);
            }
        }else{
            //file does not exist or not readable
            //send back invalid information
            write(connfd, invalid, strlen(invalid));
            close(connfd);
        }
    }
    
}