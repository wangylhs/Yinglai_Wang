#include "p1client.h"

int main(int argc, char** argv){
	if (argc != 4)
    {
        printf("usage: [IP address] [Port number] [secret-key]\n");
        exit(1);
    }    
	int port = atoi(argv[2]);
    int sockfd,n,len;
    struct sockaddr_in servaddr,cliaddr;
    //char key[SIZE];
    int i;
    //strcpy(key, argv[3]);
    char recve[SIZE];
	
    
    
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(port);
    //struct timeval before = getTime();
    len = sizeof(servaddr);
    sendto(sockfd,argv[3],strlen(argv[3]),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
    
    while (1) {
        n=recvfrom(sockfd,recve,SIZE,0,(struct sockaddr *)&servaddr,&len);
		
        int i;
        for(i=0;i<n;i++){
            write(2,&recve[i],1);
        }
        write(2,"\n",1);
    }
    
}
