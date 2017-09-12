#include "p1.h"

void readf(int argc,char* file){
    count=0;
    if(argc!=4){
        printf("Usage: [reminder-file] [server-port-number] [secret-key].\n");
        exit(0);
    }
    inFile = open(file, O_RDONLY);
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
}