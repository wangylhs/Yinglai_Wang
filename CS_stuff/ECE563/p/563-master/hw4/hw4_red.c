/******************************************************************************
* FILE: hw4_red.c
* DESCRIPTION:
*   Performs a sum of the elements in an array using a reduction clause.
* AUTHOR: Nathan Tornquist 2/15
* LAST REVISED: 02/09/15
*
* On OSX:
* g++-4.9 -o hw4_red -fopenmp hw4_red.c
*
* On ecegrid:
* gcc -o hw4_red -fopenmp hw4_red.c -std=c99
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

long long current_timestamp();

int main (int argc, char *argv[])
{
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  // INITIALIZATION LOGIC

  int cores = 4;
  int size = 10000000;

  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  omp_set_dynamic(0);     // Disable Dynamic Threads
  omp_set_num_threads(cores); // Set Num Threads (change for benchmarking)

  // Initialize a matrix
  int seed = time(NULL);
  srand(seed);

  int *a;
  a = (int *)malloc(sizeof(int)*size);
  for (int i = 0; i < size; i++)
  {
    a[i] = rand()%100;
  }

  //Time Variables
  long long t1, t2;
  long long diff;
  long long time_1, time_2;

  printf("Starting Parallel Operation\n");
  t1 = current_timestamp();

  //////////////////////////////////////////////////////////////////////
  //////////////////////// START PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////
  int row, col, off;
  double t = 0;
  double temp[cores];
  int i = 0;
  #pragma omp parallel for reduction(+:t) private(i)
  for (int i = 0; i < size; i++)
  {
    t = t + a[i];
  }
  //////////////////////////////////////////////////////////////////////
  ////////////////////////// END PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////
  t2 = current_timestamp();
  time_1 = t2 - t1;

  printf("Sum Completed\n");
  printf("Generating Solution for Verification\n");

  t1 = current_timestamp();
  double sum = 0;
  for (int i = 0; i < size; i++)
  {
    sum = sum + a[i];
  }
  t2 = current_timestamp();
  time_2 = t2 - t1;

  //VERIFY SOLUTION
  printf("Verifying Solution\n\n");

  if (sum == t)
  {
    printf("Solution Valid\n\n");
    printf("Parallel:   %f s\n", ((float)time_1)/1000);;
    printf("Sequential: %f s\n", ((float)time_2)/1000);;
    printf("Speedup: %.2f %%\n", (100*((float)time_2)/((float)time_1)));
    printf("Cores: %d\n", cores);
  }
  else {
    printf("Solution Invalid\n\n");
    printf("t:   %f\n", t);
    printf("sum: %f\n", sum);
  }

  free(a);
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
