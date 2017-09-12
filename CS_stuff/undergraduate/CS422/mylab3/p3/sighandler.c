#include "p1.h"

void sighandler(int sig)
{
    
    char buffer[30];
    char catmsg[256];
    struct timeval tv;
	const char* finish = "Finish acknowledgment.";
    
    time_t curtime;
    
    gettimeofday(&tv, NULL);
    curtime=tv.tv_sec;
    
    strftime(buffer,30,"%m-%d-%Y  %T",localtime(&curtime));

    int j;
    for(j=0;j<20;j++){
        mesg[j] = buffer[j];
    }
    mesg[j]='\0';
    //write(2,"\t",1);
    int i=0;
    int size = strlen(buf[count]);
    while(i<(size-1)){
        //write(2,&buf[count][i],1);
        catmsg[i] = buf[count][i];
        i++;
    }
    catmsg[i]='\0';
    strcat(mesg, catmsg);
    //write(2,"\n",1);
    printf("send line %d of %d.\n", (count+1), line);
    sendto(sockfd,mesg,strlen(mesg),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
    
    if(count==(line-1)){
        //exit(0);
		write(2,"Finish acknowledgment has been sent\n",36);
		sendto(sockfd,finish,strlen(finish),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
        count=0;
        return;
    }
    count++;
    alarm(delay[count]-delay[count-1]);
    
}
