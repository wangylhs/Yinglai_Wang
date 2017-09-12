#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
int crashData[MAX];
void crashReport();

int main(int argc, char** argv){
    if(argc!=2){
        fprintf(stderr, "\tUsage: ./run <program need to debug>\n");
        exit(0);
    }
    //initialize crashData
    int i;
    for(i=0; i<MAX; i++) crashData[i] = 0;
    char run[128];
    strcpy(run, "./run.sh ./");
    char* name = strdup(argv[1]);
    strcat(run, name);
    //fprintf(stdout, "runname is: %s.\n" ,run);
    FILE *data0 = fopen("curr.txt", "w");
    fputs("-1\n", data0);
    fclose(data0);
    
    fprintf(stderr, "========== Execution start ==========\n\n");
    fprintf(stderr, "Executing %d of %d...\n", 0, MAX);
    system(run);
    
    FILE *data1 = fopen("curr.txt", "w");
    fputs("1\n", data1);
    fclose(data1);
    
    
    for(i=1; i<=MAX; i++){
        fprintf(stderr, "Executing %d of %d...\n", i, MAX);
        int status = system(run);
        if(status!=0){
            fprintf(stderr, "\n++++++++Program crashed at synchronization point %d/%d ++++++++\n\n"
                    ,
                    i, MAX);
            crashData[i] = i;
        }
        FILE *data3 = fopen("curr.txt", "w");
        fprintf(data3, "%d\n", i + 1);
        fclose(data3);
    }
    fprintf(stderr, "========== Execution complete ==========\n\n");
    crashReport();
}

void crashReport(){
    fprintf(stderr, "========== Crash Report Start ==========\n");
    if(!*crashData) fprintf(stderr, "No crash ocurred.");
    else{
        int i;
        for(i=0; i<MAX; i++){
            if(crashData[i]!=0){
                fprintf(stderr, "Crash ocurred at synchronization point %d/%d\n", crashData[i],MAX);
            }
        }
    }
    fprintf(stderr, "========== Crash Report End ==========\n");
}