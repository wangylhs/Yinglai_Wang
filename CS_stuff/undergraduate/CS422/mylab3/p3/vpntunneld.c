#include "p1.h"

int main(int argc, char **argv){
  	if(argc!=2){
		printf("usage: ./vpntunneld <vpn-port-number>\n");
		exit(1);
	}
    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    if(sigaction(SIGALRM, &act, 0) == -1)
    {
        perror("sigaction");
    }
	
	char* temp = "test";
	vpnport1 = atoi(argv[1]);
	vpnport2 = vpnport1+256;			//generate a second vpn port number    
	char vpnport2s[10];
	tostring(vpnport2s, vpnport2);
	printf("vpnport2 is: %s\n", vpnport2s);
	serverPort = 0;	

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(vpnport1);
    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    
    len = sizeof(cliaddr);
    memset(mesg,0,SIZE);

		//receiving sever IP and server port number
		memset(mesg,0,SIZE);
		recvfrom(sockfd,mesg,SIZE,0,(struct sockaddr *)&cliaddr,&len);	
		//save server ip		
		serverIP = strdup(mesg);	
		printf("server ip is %s\n",serverIP);		
		memset(mesg,0,SIZE);			
		recvfrom(sockfd,mesg,SIZE,0,(struct sockaddr *)&cliaddr,&len);
		//save server port number
		serverPort = atoi(mesg);
		sendto(sockfd,vpnport2s,strlen(vpnport2s),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));		
		printf("server port is %d\n", serverPort);
		printf("client port is %d\n",cliaddr.sin_port);
        printf("client ip is %s\n",inet_ntoa(cliaddr.sin_addr));
			
	
	fprintf(stdout,"start listening to mobclient\n");
	//bind second port number
	sockfd2=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(vpnport2);
    bind(sockfd2,(struct sockaddr *)&servaddr,sizeof(servaddr));
    
	//receive the secret key from mobclient
	memset(mesg,0,SIZE);
	n = recvfrom(sockfd2,receiv,SIZE,0,(struct sockaddr *)&cliaddr,&len);
	mobport = cliaddr.sin_port;	
	printf("mob client port is %d\n",mobport);
	mobilIP = strdup(inet_ntoa(cliaddr.sin_addr));
	printf("mob client ip is %s\n",inet_ntoa(cliaddr.sin_addr));
	
	int i;
    for(i=0;i<n;i++){
        write(2,&receiv[i],1);
    }
    write(2,"\n",1);

	//send secret key to real server
	if(serverPort!=0) sendkey();
    
    
	fprintf(stdout,"start receiving and forwarding...");
	
    int oldlen = len;
	//receiving from real server and forward to mob client
	while(1){
		len = sizeof(realserver);
		memset(receiv,0,SIZE);
		n = recvfrom(sockfds,receiv,SIZE,0,(struct sockaddr *)&realserver,&len);
        
		sendto(sockfd2,receiv,strlen(receiv),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
		for(i=0;i<n;i++){
            write(2,&receiv[i],1);
        }
        write(2,"\n",1);
		
		
	}
	








    return 0;
}
