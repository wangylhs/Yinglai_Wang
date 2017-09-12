#include "p1client.h"

int main(int argc, char** argv){
	if (argc != 5)
    {
        printf("usage: ./vpntunnel <vpn-IP> <vpn-port> <server-IP> <server-port-number>\n");
        exit(1);
    }
    int vpnport = atoi(argv[2]);
	int vpnport2=0;
	int serverport = atoi(argv[4]);
	char* serverIP = strdup(argv[3]);
    int sockfd,n,len;
    struct sockaddr_in servaddr,cliaddr;
    int i;
    char recv[SIZE];
    
    
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);	//using vpnIP
    servaddr.sin_port=htons(vpnport);				//using vpnport
    len = sizeof(servaddr);	
	//sending server-IP and server-port-number
		for(i=0; i<2; i++){
			sendto(sockfd,argv[i+3],strlen(argv[i+3]),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
			printf("sending %s to %d\n", argv[i+3], vpnport);
		}
    
    //receiving second port number
	while(1){
        n=recvfrom(sockfd,recv,SIZE,0,(struct sockaddr *)&servaddr,&len);
		vpnport2 = atoi(recv);
		free(serverIP);
		if(vpnport2!=0){
			printf("vpn-IP user should use is %s\n", argv[1]);
			printf("second port number is: %d\n", vpnport2);
			exit(0);	
		}
		/*
        int i;
        for(i=0;i<n;i++){
            write(2,&recv[i],1);
        }
        write(2,"\n",1);
		*/
    }
    
}
