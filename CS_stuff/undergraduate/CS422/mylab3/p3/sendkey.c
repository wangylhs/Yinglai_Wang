#include "p1.h"


void sendkey(){
	sockfds = socket(AF_INET,SOCK_DGRAM,0);
    bzero(&realserver,sizeof(realserver));
    realserver.sin_family = AF_INET;
	//printf("ip is %s\n", serverIP);
    realserver.sin_addr.s_addr=inet_addr(serverIP);
    realserver.sin_port=htons(serverPort);
    if(bind(sockfds,(struct sockaddr *)&realserver,sizeof(realserver)) < 0){
		//perror("bind error");
		//exit(1);	
	}
	//fprintf(stdout,"before send........");	
	
	
	sendto(sockfds,receiv,strlen(receiv),0,(struct sockaddr *)&realserver,sizeof(realserver));
	

}
