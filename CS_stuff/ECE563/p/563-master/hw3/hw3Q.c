#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


long long current_timestamp();


typedef struct Q {
   int* q;
   int pos;
   int size;
} Q;

struct Q* initQ(int n) {
   int i;
   struct Q *newQ = (struct Q *) malloc(sizeof(Q));   
   newQ->q = (int*) malloc(sizeof(int)*n);
   newQ->pos = -1;
   newQ->size = n-1;
}

void putWork(struct Q* workQ) {
   if (workQ->pos < (workQ->size)) {
      workQ->pos++;
      workQ->q[workQ->pos] = (int) ((double)rand() / (double) RAND_MAX * (workQ->pos/1000));
   } else printf("ERROR: attempt to add Q element%d\n", workQ->pos+1);
}

int getWork(struct Q* workQ) {
   if (workQ->pos > -1) {
      int w = workQ->q[workQ->pos];
      workQ->pos--;
      return w;
   } else printf("ERROR: attempt to get work from empty Q%d\n", workQ->pos);
}

bool workExists(struct Q* workQ) {
  return (workQ->pos > -1);
}


int main (int argc, char *argv[]) {
  int i = 0;

  //Seed Random
  int seed = time(NULL);
  srand(seed);

  //Time Variables
  long long t1, t2;
  long long diff;
  long long time;

  int threads = 1;
  omp_set_num_threads(threads);

  int size = 100000;
  struct Q *newQ = initQ(size);

  for (i = 0; i < size; i++) {
    putWork(newQ);
  }


  t1 = current_timestamp();

  //Logic, parallel or sequential depending on the number of cores
  #pragma omp parallel shared(newQ)
  {
    while(workExists(newQ)) {
      #pragma omp critical
      if (workExists(newQ))
        int work = getWork(newQ);
    }
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
