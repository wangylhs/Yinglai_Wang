#include "p1c.h"
#define BLOCK 128
#define SIZE 132
#define MAX 8192


int main(int argc, char** argv){
    if (argc != 5)
    {
        printf("usage: <IP address> <Port number> <file-path> <filename>\n");
        exit(1);
    }
    //variables used to build connection with server
    int sockfd,n;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len;
    //create variables for data handling
    int seq;
    char seqs[4];
    char data[8][BLOCK+1];
    //char content[BLOCK];
    int i;
    for(i=0; i<8; i++) memset(data[i], 0, BLOCK);
    
    char recbuf[SIZE];
    memset(recbuf, 0, SIZE);
    int port = atoi(argv[2]);
    const char* invalid = "INVALID REQUEST";
    const char* end = "END ACK";
    //create connection
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(port);
    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    //send file path to server
    n = sendto(sockfd, argv[3], strlen(argv[3]), 0, (struct sockaddr *)&servaddr,sizeof(servaddr));
    fprintf(stdout, "mesg is %d %s\n", n, argv[3]);
    //program exit if error on write
    if(n<0){
        perror("error on sending file path");
        exit(1);
    }
    //start receiving if send succeed
    int count = 0;                                              //counter for send ack back
    char marker[8];                                             //to mark the missing packet
    memset(marker, 0, 8);
    while(1){
        //prepare to download file
        int outfd = open(argv[4], O_WRONLY | O_CREAT, 0644);    //create file

        len = sizeof(servaddr);
        while((n=recvfrom(sockfd, recbuf, SIZE, 0, (struct sockaddr*)&servaddr, &len))>0){
            //fprintf(stderr, "recbuf is %s\n", recbuf);
            if(strncmp(recbuf,invalid, strlen(invalid))==0){
                printf("%s\n", invalid);
                exit(0);
            }else if(strncmp(recbuf, end, strlen(end))==0){
                close(outfd);
                printf("download completed.\n");
                exit(0);
            }else{
                printf("count = %d\n", count);
                
                memset(seqs, 0, 4);
                strncat(seqs, recbuf, sizeof(int));
                seq = atoi(seqs);
                marker[seq%8] = 1;
                //char* mesg = recbuf+1;
                strncpy(data[seq%8], recbuf+1, strlen(recbuf+1));
				*(data[seq%8]+strlen(recbuf+1)) = 0;
                fprintf(stderr, "recbuf is %s\n", recbuf);
                fprintf(stdout, "content is %s\n", data[seq%8]);
                write(outfd, &data[seq%8], strlen(data[seq%8]));
                /*
                 if(seq%8==7){
                     fprintf(stdout,"reach in 8th =====\n");
                     int i;
                     int sum=0;
                     //send ack back
                     for(i=0;i<8;i++){
                         fprintf(stdout, "marker[%d] is %d\n", i ,marker[i]);
                         sum += marker[i];
                     }
                     sendto(sockfd, marker, 8, 0, (struct sockaddr *)&servaddr,sizeof(servaddr));
                     memset(marker, 0, 8);
                     //if all packets received, write content to the file
                     if(sum==8){
                         for(i=0; i<8; i++){
                             write(outfd, &data[i], strlen(data[i]));
                             //clear data buffer
                             memset(data[i], 0, BLOCK);
                         }
                     }
                 }
            */
                
            }
            
            memset(recbuf, 0, BLOCK);
            memset(data[seq%8], 0, BLOCK);
            //increment stuff
            count++;
            
        }
        close(outfd);
        close(sockfd);
    }
}



















