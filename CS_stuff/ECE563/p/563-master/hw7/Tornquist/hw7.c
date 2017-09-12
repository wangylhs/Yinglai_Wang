/******************************************************************************
* FILE: hw7.c
* DESCRIPTION:
*   Sums an array of elements using mpi collective communication
* AUTHOR: Nathan Tornquist 2/24
* LAST REVISED: 02/24/15
*
* Compile the program:
* mpicc hw7.c -o hw7
*
* Execute the program:
* qsub -l nodes=1:ppn=16,walltime=00:01:00 ./hw7.sub
******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define MASTER 0

long long current_timestamp();

int main (int argc, char *argv[])
{
  int i = 0;
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  // INITIALIZATION LOGIC

  int array_size = 10000;

  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  // Initialize an array
  int seed = time(NULL);
  srand(seed);

  int *a;
  a = (int *)malloc(sizeof(int)*array_size);
  for (i = 0; i < array_size; i++)
  {
    a[i] = rand()%100;
  }

  //Time Variables
  long long t1, t2;
  long long diff;
  long long time_1, time_2;

  /* MPI Parameters */
  int rank, size, len;
  char name[MPI_MAX_PROCESSOR_NAME];

  double t = 0;
  double localsum = 0;

  t1 = current_timestamp();

  //////////////////////////////////////////////////////////////////////
  //////////////////////// START PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////
  MPI_Init(&argc, &argv);                 /* start MPI           */
  //Not really needed, but potentially useful
  MPI_Comm_size(MPI_COMM_WORLD, &size);   /* get number of ranks */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);   /* get rank            */
  MPI_Get_processor_name(name, &len);     /* get run-host name   */

  int start = array_size/size*rank;
  int end = array_size/size*(rank + 1) - 1;
  if (rank == size -1) {
    end = array_size - 1;
  }
  for (i = start; i <= end; i++) {
    localsum = localsum + a[i];
  }

  MPI_Reduce(&localsum, &t, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();                         /* terminate MPI       */
  //////////////////////////////////////////////////////////////////////
  ////////////////////////// END PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////
  t2 = current_timestamp();
  time_1 = t2 - t1;

  if (rank == 0) {
    printf("Sum Completed\n");
    printf("Generating Solution for Verification\n");

    t1 = current_timestamp();
    double sum = 0;
    for (i = 0; i < array_size; i++)
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
    }
    else {
      printf("Solution Invalid\n\n");
      printf("t:   %f\n", t);
      printf("sum: %f\n", sum);
    }

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
