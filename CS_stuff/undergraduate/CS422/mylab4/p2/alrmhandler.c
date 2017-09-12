#include "p2.h"

void alrmhandler(int sig){
    if(timeoutflag == 1){
        chatting = 0;
        fprintf(stdout,"no response.\n>");
    }
    return;
}
