#include "p1.h"

int main(int argc, char **argv){
    count=0;
    if(argc!=2){
        printf("Usage: Please put an file name as argument.\n");
        exit(0);
    }
    inFile = open(argv[1], O_RDONLY);
    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    if(sigaction(SIGALRM, &act, 0) == -1)
    {
        perror("sigaction");
    }
    
    int n;
    char c;
    char temp[10];
    line = 0;
    int i=0;
    int j=0;
    while((n=read(inFile,&c,1))!=0){
        if(c>=48&&c<=57){
            temp[i]=c;
            //printf("%c",temp[i]);
            i++;
        }else{
            buf[line][j]=c;
            j++;
            if(c=='\n'){
                temp[i+1]='\0';
                int sec=atoi(temp);
                delay[line]=sec;
                //printf("sec: %d\n",sec);
                i=0;
                line++;
                j=0;
            }
        }
        
        
    }
    alarm(delay[0]);
    while(1);
    return 0;
}