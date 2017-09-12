#include "p3.h"

int main(int argc, char** argv){
    if(argc!=2){
        printf("usage: ./mypingd <Port number>\n");
        exit(1);
    }
    //register signal handler
    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(sigaction(SIGCHLD, &act, 0) == -1){
        perror("sigaction error");
        exit(1);
    }
    
    //create server
    int port = atoi(argv[1]);
    int listenfd,connfd,n;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t clilen;
    pid_t     childpid;
    char mesg[SIZE];
    
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);
    if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0){
        perror("error on binding");
        exit(1);
    }
    
    
    listen(listenfd,5);
    clilen=sizeof(cliaddr);
    while(1)
    {
        
        connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
        if(connfd<0){
            //perror("error on accept");
            //exit(1);
        }
        childpid = fork();
        if(childpid<0){
            perror("error on fork");
            exit(1);
        }
        
        if (childpid == 0)
        {
            close (listenfd);
            printf("child process...\n");
            //n = recvfrom(connfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&clilen);
            //bzero(mesg, SIZE);
            n = read(connfd, mesg, SIZE);
            if(n<0){
                //perror("error reading from socket");
                //exit(1);
            }
            //sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
            n = write(connfd, mesg, SIZE);
            if(n<0){
                //perror("error writing to socket");
                //exit(1);
            }
            exit(0);
        }else{
            close(connfd);
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
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
     */
    
}





