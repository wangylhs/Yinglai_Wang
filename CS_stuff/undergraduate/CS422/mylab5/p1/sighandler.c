#include "p1.h"

void sighandler(int sig){
    
    //register sighandler again
    
    signal(sig, sighandler);
    
    printf("child process end\n");
    wait(NULL);
    
}