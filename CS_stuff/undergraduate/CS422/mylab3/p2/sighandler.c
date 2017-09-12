#include "p3.h"

void sighandler(int sig){
    signal(sig, sighandler);
    if(sig==SIGCHLD){
        printf("Child process ended\n");
        wait(NULL);
    }
}