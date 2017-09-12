#include "p3.h"


int main(int argc, char** argv){
    int sockfd,n;
    struct sockaddr_in from;
    struct sockaddr_in dest_addr;
    socklen_t len;
    int nsend = 0, nreceived = 0;
    

    
    unsigned long inaddr = 01;
    struct hostent *host;
    
    int size = 1024;    //default payload size
    int sockfd,n,len;
    struct sockaddr_in servaddr,cliaddr;
    if(argc==4){
        if(argv[1]=="-s"){
            size = atoi(argv[2]);   //customized payload size
            host = gethostbyname(argv[3]);
        }else{
            printf("usage: ./myping -s <payload size(byte)> <host name>\n");
            printf("usage: ./myping <host name>\n");
            exit(1);
        }
        
    }else if(argc==2){
        host = gethostbyname(argv[1]);
        
    }else{
        printf("usage: ./myping -s <payload size(byte)> <host name>\n");
        printf("usage: ./myping <host name>\n");
        exit(1);
    }
    //initialize data
    char sendline[size];
    int i;
    for(i=0;i<size;i++) sendline[i]='0';
    char recvline[size];
    
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&dest_addr, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    if(host==NULL){
        perror("gethostbyname error");
        exit(1);
    }
    memcpy((char*)&dest_addr.sin_addr, host->h_addr, host->h_length);
    if(argc==2) printf("PING %s(%s): %d bytes of data.\n", argv[1], inet_ntoa(dest_addr.sin_addr), size);
    if(argc==4) printf("PING %s(%s): %d bytes of data.\n", argv[3], inet_ntoa(dest_addr.sin_addr), size);
    struct timeval before = getTime();          //record the sending time
    len = sizeof(dest_addr);
    sendto(sockfd, sendline, size, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    n=recvfrom(sockfd, recvline, sizeof(recvline), 0, (struct sockaddr *)&from, &len);
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
    
    
    /*
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
   */
    
}