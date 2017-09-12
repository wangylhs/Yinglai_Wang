#include "p1.h"
#define BLOCK 128
#define SIZE 132               //actual size of each packet
#define MAX 8192

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
    int sockfd,n;
    int port = atoi(argv[1]);
    struct sockaddr_in servaddr,cliaddr;
    socklen_t clilen;
    pid_t pid;
    int taskflag = 0;
    int seq, iter;                                //sequence # of packet
    char seqs[4];                               //string of seq
    //seqs = (char*)malloc(sizeof(char)*4);
    char data[8][BLOCK+1];                    //two dimension array to store a window of data
    
    int i;
    for(i=0; i<8; i++){
        memset(data[i], 0, BLOCK);
    }
    char buf[BLOCK+1];                          //temp buffer to read file
    //buf = (char*)malloc(BLOCK);
    memset(buf, 0, BLOCK);
    const char* invalid = "INVALID REQUEST";
    const char* end = "END ACK";
    char mesg[SIZE+1];
    //mesg = (char*)malloc(sizeof(char)*SIZE+2);
    memset(mesg,0,SIZE);
    
    while(1){
    label:
        fprintf(stderr,"start====\n");
        sockfd=socket(AF_INET,SOCK_DGRAM,0);
        
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        servaddr.sin_port=htons(port);
        bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
        
        seq = 0;
        iter = 0;
        //receive message from client
        clilen = sizeof(cliaddr);
        memset(mesg,0,SIZE);
        //fprintf(stderr, "mesg is %s\n", mesg);
        //check file existence, check read access
        n = recvfrom(sockfd, &mesg, SIZE, 0, (struct sockaddr*)&cliaddr, &clilen);
        fprintf(stderr, "mesg is %s\n", mesg);
        int val1, val2;
        val1 = access(mesg, F_OK);
        val2 = access(mesg, R_OK);
        if(val1 != 0 || val2 != 0 && strlen(mesg)<1){                      //file does not exist or not readable
            fprintf(stderr, "invalid file path\n");
            
            //send back invalid information
            sendto(sockfd, invalid, 15, 0, (struct sockaddr *)&cliaddr,sizeof(cliaddr));
            close(sockfd);
            goto label;
        }else{
            //file exist and readable
            fprintf(stderr, "file exist and readable\n");
            /*pid = fork();
             if(pid == 0){*/
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
            int in, out;
            int infd = open(mesg, O_RDONLY);
            memset(mesg, 0, SIZE);
            memset(buf, 0, BLOCK);
            
            while((in=read(infd, buf, BLOCK))>0){
				*(buf+in) = 0;
                //fprintf(stderr, "reaches here================\n");
                /*
                if(iter%8==0 && iter!=0){
                    fprintf(stderr, "reach in 8th ======\n");
                    char temp[8];
                    int i;
                    memset(temp, 0, 8);
                    clilen = sizeof(cliaddr);
                    recvfrom(sockfd, &temp, 8, 0, (struct sockaddr*)&cliaddr, &clilen);
                    int sum=0;
                    for(i=0; i<8; i++){
                        fprintf(stdout,"temp[%d] is %d\n", i, temp[i]);
                        sum += temp[i];
                    }
                    if(sum==8){
                        goto label2;
                    }
                    
                    for(i=0; i<8; i++){
                        if(temp[i]=='0'){
                            memset(seqs, 0, 4);
                            snprintf(seqs, sizeof(seqs), "%d", i);
                            strcat(mesg, seqs);
                            strcat(mesg, data[i]);
                            fprintf(stdout, "this is extra send %s\n", mesg);
                            sendto(sockfd, mesg, strlen(mesg), 0, (struct sockaddr *)&cliaddr,sizeof(cliaddr));
                            memset(mesg,0,SIZE);
                        }
                    }
                label2:
                    for(i=0;i++;i<8) memset(data[i], 0, BLOCK);
                }
                */
                //store data
                fprintf(stdout, "buf is %s\n", buf);
                memset(data[seq%8], 0, BLOCK);
                strncpy(data[seq%8], buf, strlen(buf));
				*(data[seq%8]+strlen(buf)) = 0;
                //memset(buf, 0, BLOCK);
                
                //create packet
                memset(seqs, 0, 4);
                seq = seq%8;
                snprintf(seqs, sizeof(seqs), "%d", seq);
                strncpy(mesg, seqs, sizeof(int));
                strncat(mesg, data[seq%8], strlen(buf));
                
                
                //send packet
                fprintf(stdout, "data is %s\n", data[seq%8]);
                fprintf(stdout, "mesg send is %s\n", mesg);
				fprintf(stdout, "SIZE: %d\n", strlen(buf)+sizeof(int));
				*(mesg+strlen(buf)+sizeof(int)) = 0;
                out = sendto(sockfd, mesg, strlen(mesg), 0, (struct sockaddr *)&cliaddr,sizeof(cliaddr));
                if(out<0){
                    perror("error on send");
                }
                //clear all buffers
                memset(data[seq%8], 0, BLOCK);                   //will be delete after
                memset(buf, 0, BLOCK);
                memset(mesg, 0, SIZE);
                
                //increment stuff
                iter++;
                seq++;
            }
            //send end ack and clear buffers
            memset(mesg, 0, SIZE);
            for(i=0; i<8; i++){
                memset(data[i], 0, BLOCK);
            }

            sendto(sockfd, end, 7, 0, (struct sockaddr *)&cliaddr,sizeof(cliaddr));
            //print time after finish read file
            gettimeofday(&tv, NULL);
            curtime=tv.tv_sec;
            msec=tv.tv_usec/1000;
            strftime(timebuffer,30,"%m-%d-%Y  %T",localtime(&curtime));
            write(1,&timebuffer,24);
            printf(".%dms\n", msec);
            close(infd);
            //exit(0);
            //}else{
            close(sockfd);
            goto label;
        }
        close(sockfd);
        goto label;
        
    }
    
}
