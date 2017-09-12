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
  long long time_1, time_2;

  int i = 0;
  t1 = current_timestamp();

  int threads = 4;
  omp_set_num_threads(threads);

  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    switch(tid)
    {
      case 0:
        for (i = 0; i < size/4; i++) { doWork(wA[i]); }
        break;
      case 1:
        for (i = size/4*1; i < size/4*2; i++) { doWork(wA[i]); }
        break;
      case 2:
        for (i = size/4*2; i < size/4*3; i++) { doWork(wA[i]); }
        break;
      case 3:
        for (i = size/4*3; i < size/4*4; i++) { doWork(wA[i]); }
        break;
    }
  }
  t2 = current_timestamp();
  time_1 = t2 - t1;

  t1 = current_timestamp();
  for (i = 0; i < size; i++)
  {
    doWork(wA[i]);
  }
  t2 = current_timestamp();
  time_2 = t2 - t1;

  printf("Parallel:   %f s\n", ((float)time_1)/1000);;
  printf("Sequential: %f s\n", ((float)time_2)/1000);;
  printf("Speedup: %.2f %%\n", (100*((float)time_2)/((float)time_1)));
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
