#include "p2.h"


int main(int argc, char **argv){
    struct stat st;
    stat(argv[1],&st);
    int size = st.st_size;
    char* buf;
    buf=(char*)malloc((size-8)*sizeof(char));
    inFile = open(argv[1], O_RDONLY);
    unsigned char c;
    uint64_t checksum=0;
    uint64_t bigsum;
    int n;
    int i=0;
    while((n=read(inFile,&c,1))!=0){
        if(i==(size-9)){
            read(inFile,&bigsum,8);
        }
        buf[i] = c;
        checksum += buf[i];
        i++;
    }
    
    //printf("%lx\n", checksum);
    //printf("%lx\n", bigsum);
    uint64_t litsum = convertEndian(bigsum);
    printf("The check value that just been calculated: %lx\n", checksum);
    printf("The check value that convert back from the last 8 bytes: %lx\n", litsum);
    if(checksum==litsum){
        printf("%s has not been crrupted.\n",argv[1]);
    }else{
        
        //if the output file does not exist, create one
        FILE *fp;
        fp=fopen(argv[2],"w");
        fclose(fp);
        outFile = open(argv[2], O_WRONLY | O_APPEND);
        for(i=0;i<(size-8);i++){
            write(outFile,&buf[i],1);
        }
        printf("Crrupted! New result have been saved to %s.\n",argv[2]);
    }
    
    
    
    
    
}