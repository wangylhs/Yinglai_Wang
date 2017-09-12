#include "p4.h"

void sighandler(int sig){
    printf("Server is not reachable.\n");
    exit(0);
}
