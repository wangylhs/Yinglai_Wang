#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

void helpMessage(){
    printf("Usage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input. PATTERN is a\nstring. grep-lite will search standard input line by\nline, and (by default) print out those lines which\ncontain pattern as a substring.\n\n  -v, --invert-match     print non-matching lines\n  -n, --line-number      print line number with output\n  -q, --quiet            suppress all output\n\nExit status is 0 if any line is selected, 1 otherwise;\nif any error occurs, then the exit status is 2.\n\n");
}


int main(int argc, char** argv){
    int help=0;
    int invert=0;
    int line=0;
    int quiet=0;
    char* pattern = argv[argc-1];
    int i;
    
    for(i=1;i<argc-1;i++){
        if(strcmp(argv[i],"--help")==0) help=1;
        else if(strcmp(argv[i],"--invert-match")==0) invert = 1;
        else if(strcmp(argv[i],"-v")==0) invert=1;
        else if(strcmp(argv[i],"--line-number")==0) line=1;
        else if(strcmp(argv[i],"-n")==0) line=1;
        else if(strcmp(argv[i],"-q")==0) quiet=1;
        else if(strcmp(argv[i],"--quiet")==0) quiet=1;
    }
    if(help || strcmp(pattern, "--help")==0){
        helpMessage();
        return EXIT_SUCCESS;
    }
    if(argc==1){
        fprintf(stderr,"argument error!\n");
        return FALSE;
    }
    
    int size = 2050;
    char buf[size];
    int found = 0;
    int current = 0;
    int match = 0;
    while (fget(buf,size,stdin)!=NULL) {
        current++;
        match = (strstr(buf,pattern)!=NULL);
        if((!match && invert) || (match && !invert)){
            found = 1;
            if (!quiet) {
                if (line) {
                    printf("%d:", current);
                }else{
                    printf("%s", buf);
                }
            }
        }
    }
    return found ? 0 : 1;

        
}