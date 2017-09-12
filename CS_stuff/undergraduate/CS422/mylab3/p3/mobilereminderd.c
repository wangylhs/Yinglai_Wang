#include "p1.h"

int main(int argc, char **argv){
  	
    char* key;			//used to save the received secret key
    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    if(sigaction(SIGALRM, &act, 0) == -1)
    {
        perror("sigaction");
    }
    //read file
    readf(argc,argv[1]);
    //create server
    server(argv[2]);
    
    const char* acknow = "key matches! Start transfer data.";
    while(1)
    {
        len = sizeof(cliaddr);
        memset(mesg,0,SIZE);
        n = recvfrom(sockfd,mesg,SIZE,0,(struct sockaddr *)&cliaddr,&len);
        //printf("recving");
        //save mesg to key
		key = (char*)malloc(sizeof(char)*strlen(mesg));
		strcpy(key,mesg);
        
        if(strlen(key)==strlen(argv[3]) && strncmp(key, argv[3], strlen(argv[3]))==0){
            printf("secret key matches.\n");
            sendto(sockfd,acknow,strlen(acknow),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
            alarm(delay[0]);
            
        }
		free(key);

    }
    return 0;
}
