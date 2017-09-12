#include "p3.h"

int main(int argc, char** argv){
    //register signal handler
    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    if(sigaction(SIGCHLD, &act, 0) == -1)
    {
        perror("sigaction");
    }
    
    //create a server
    port = atoi(argv[1]);
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);
    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    
    pid_t childPID;
    
    while(1)
    {
        len = sizeof(cliaddr);
        n = recvfrom(sockfd,mesg,SIZE,0,(struct sockaddr *)&cliaddr,&len);
        
        childPID = fork();
        if(childPID >= 0)   //fork succeed
        {
            if(childPID == 0)   //child process
            {
                printf("Child process: send back to client.\n");
                sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
                exit(0);        //sighandler is invoked
                
            }
            else                //parent process
            {
                printf("Parten: keep receiving...\n");
                n = recvfrom(sockfd,mesg,SIZE,0,(struct sockaddr *)&cliaddr,&len);
            }
        }else               //fork failed
        {
            printf("fork failed.\n");
            return 1;
        }
        
        //sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
        //printf("Message received.\n");
    }
    
}





