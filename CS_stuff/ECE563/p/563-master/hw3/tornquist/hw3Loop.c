#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

void doWork(int t) {
   usleep(t*1000);
}

long long current_timestamp();

int* initWork(int n) {
   int i;
   double r;
   int* wA = (int *) malloc(sizeof(int)*n);   
   for (i = 0; i < n; i++) {
      //Changed to work better with usleep
      wA[i] = (int) ((double)rand() / (double) RAND_MAX * (i+10));
   }
   return wA;
}

int main (int argc, char *argv[]) {
  //Seed Random
  int seed = time(NULL);
  srand(seed);

  //Declare Variables
  int size = 400;
  int *wA;
  wA = initWork(size);

  //Time Variables
  long long t1, t2;
  long long diff;
  long long time;

  int i = 0;
  t1 = current_timestamp();
  #pragma omp parallel for private(i) schedule(dynamic)
  for (int i = 0; i < size; i++)
  {
    doWork(wA[i]);
  }
  t2 = current_timestamp();
  time = t2 - t1;
  printf("Time:   %f s\n", ((float)time)/1000);;
}

//FROM a StackOverflow article on calculating accurate times
//http://stackoverflow.com/questions/3756323/getting-the-current-time-in-milliseconds
long long current_timestamp() {
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
  //printf("milliseconds: %lld\n", milliseconds);
  return milliseconds;
}
