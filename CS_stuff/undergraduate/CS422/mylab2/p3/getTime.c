#include "p3.h"

struct timeval getTime(){
    struct timeval tv;
    time_t curtime;
    gettimeofday(&tv, NULL);
    return tv;
}