#include "p2.h"

int main(int argc, char **argv){
    struct stat st;
    stat(argv[1],&st);
    int size = st.st_size;
    char* buf;
    buf=(char*)malloc(size*sizeof(char));
    //if the output file does not exist, create one
    FILE *fp;
    fp=fopen(argv[2],"w");
    fclose(fp);
    
    inFile = open(argv[1], O_RDONLY);
    outFile = open(argv[2], O_WRONLY | O_APPEND);
    unsigned char c;
    uint64_t checksum=0;
    int n;
    int i=0;
    while((n=read(inFile,&c,1))!=0){
        buf[i] = c;
        checksum += buf[i];
        i++;
    }
    
    for(i=0;i<size;i++){
        write(outFile,&buf[i],1);
    }
    //printf("%lx\n", checksum);
    uint64_t chksm = convertEndian(checksum);
    //printf("%lx\n", chksm);
	write(outFile, &chksm, sizeof(uint64_t));
    
}