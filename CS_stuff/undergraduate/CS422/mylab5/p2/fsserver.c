#include "p1.h"


int main(int argc, char** argv){
    if(argc!=2){
        printf("usage: ./fsserver <Port number>\n");
        exit(1);
    }
    //resigter signal handler
    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(sigaction(SIGCHLD, &act, 0) == -1){
        perror("sigaction error");
        exit(1);
    }
    //variables used to create server and build the connection
    int port = atoi(argv[1]);
    int n;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t clilen;
    pid_t     pid;                          //process ID
    
    const char* invalid = "INVALID REQUEST";
    const char* end = "END ACK";
    //create server
    listenfd = socket(AF_INET, SOCK_STREAM,0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);
    //exit program if bind fails
    if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0){
        perror("error on binding");
        exit(1);
    }
    //start listening
    listen(listenfd, 5);
    clilen = sizeof(cliaddr);
    while(1){
        //build connection with client
        connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
        if(connfd<0){
            //perror("error on accept");
            //exit(1);
        }
        //receive message from client
        memset(mesg,0,SIZE);
        n = read(connfd, mesg, SIZE);
        
        //check file existence, check read access
        int val1, val2;
        val1 = access(mesg, F_OK);
        val2 = access(mesg, R_OK);
        if(val1==0 && val2==0){     //file exist and readable
            fprintf(stderr, "file exist and readable\n");
            //create child process to do the rest
            pid = fork();
            if(pid==0){
                //child process
                close(listenfd);
                fprintf(stderr, "child process begin...\n");
                
                //record time (this the time before first read)
                struct timeval tv;
                time_t curtime;
                int msec;
                char timebuffer[30];    //buffer to save the string of time
                gettimeofday(&tv, NULL);
                curtime=tv.tv_sec;
                msec=tv.tv_usec/1000;
                strftime(timebuffer,30,"%m-%d-%Y  %T",localtime(&curtime));
                //printf current time
                write(1,&timebuffer,24);
                printf(".%dms\n", msec);
                //read file by fixed block size
                int in, infd, out;
                infd = open(mesg, O_RDONLY);
                while((in=read(infd, &buf, BLOCK))>0){
                    /*int i;
                    for(i=0; i<BLOCK;i++){
                        printf("%c",buf[i]);
                    }*/
                    out = write(connfd, buf, BLOCK);
                    if(out<0){
                        perror("error on write");
                    }
                }
                //send finish ack
                write(connfd, end, strlen(end));
                //print time after finish read file
                gettimeofday(&tv, NULL);
                curtime=tv.tv_sec;
                msec=tv.tv_usec/1000;
                strftime(timebuffer,30,"%m-%d-%Y  %T",localtime(&curtime));
                write(1,&timebuffer,24);
                printf(".%dms\n", msec);
                close(infd);
                
                exit(0);    //sighandler invoked
            }else{
                //parent process
                close(connfd);
            }
            
        }else{                      //file does not exist or not readable
            //send back invalid information
            write(connfd, invalid, strlen(invalid));
            close(connfd);
        }
        
        
        
    }
    
    
    
    
}