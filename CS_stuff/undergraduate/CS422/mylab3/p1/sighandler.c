#include "p3.h"

void sighandler(int sig){
    if(sig==SIGCHLD){
        printf("Child process ended\n");
        wait(NULL);
    }
}