#include "p1.h"

void sighandler(int sig)
{
    
    char buffer[30];
    struct timeval tv;
    
    time_t curtime;
    
    gettimeofday(&tv, NULL);
    curtime=tv.tv_sec;
    
    strftime(buffer,30,"%m-%d-%Y  %T",localtime(&curtime));
    //printf("%s%ld\n",buffer,tv.tv_usec);
    int j;
    for(j=0;j<20;j++){
        write(2,&buffer[j],1);
    }
    write(2,"\t",1);
    int i=0;
    int size = strlen(buf[count]);
    while(i<(size-1)){
        write(2,&buf[count][i],1);
        i++;
    }
    write(2,"\n",1);
    //write(1,buf[count],strlen(buf[count]));
    
    if(count==(line-1)) exit(0);
    count++;
    alarm(delay[count]-delay[count-1]);
    
}
