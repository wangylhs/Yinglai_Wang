#include "p2.h"

void iohandler(int sig){
        int n;
    
        const char* start = "letschat";     /* Chat start informer */
        do{
            /* chat flag = 1, means there is a chat alive */
            chatting = 1;
            timeoutflag = 0;
            clilen = sizeof(cliaddr);
            memset(recvbuf,0,1024);
            
            if ((recvMsgSize = recvfrom(sock, recvbuf, 1024, 0,(struct sockaddr *) &cliaddr, &clilen)) < 0) {
                /* Only acceptable error: recvfrom() would have blocked */
                //perror("recvfrom() failed");
            }
            
            /* ko = denial, ok = accept */
            if(strncmp(recvbuf,"ko",2)==0){
                fprintf(stdout,"\n>doesn't want to chat\n>");
                chatting = 0;
                break;
            }else if(strncmp(recvbuf,start,7)==0){
                fprintf(stdout,"\n>chat request from %s %d", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
                /* when chat request arrives, set the target IP and port to the right value */
                sourceIP =strdup(inet_ntoa(cliaddr.sin_addr));
				recvfrom(sock, recvbuf, 1024, 0,(struct sockaddr *) &cliaddr, &clilen);
				sourceport = atoi(recvbuf);
				target.sin_addr.s_addr=inet_addr(sourceIP);
    			target.sin_port=htons(sourceport);
                
            }else if(strncmp(recvbuf,"ok",2)==0){
                /* request accepted, chat flag is true now */
                timeoutflag = 0;
                chatting = 1;
                fprintf(stdout,"\n>chat request accepted");
            }else{
                /* when an incoming message interrupts current message, preserve current message and print it after printing the incoming message  */
                if(strlen(recvbuf)==0)
                    fprintf(stdout,"\n>%s", str);
                else
                    fprintf(stdout,"\n>%s", recvbuf);
                
            }
            memset(recvbuf,0,1024);
        }while(recvMsgSize>=0);
}
