#include "p1.h"

void server(char* p){
    port = atoi(p);
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);
    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
 

}
