/******************************************************************************
* FILE: hw8.c
* DESCRIPTION:
*   Simulates a work queue with workers
* AUTHOR: Nathan Tornquist 2/24
* LAST REVISED: 02/24/15
*
* Compile the program:
* mpicc hw8.c -o hw8
*
* Execute the program:
* qsub -l nodes=1:ppn=16,walltime=00:01:00 ./hw8.sub
******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#define MASTER 0
#define WORK_TAG 1
#define COMPLETE_TAG 2
long long current_timestamp();

int main (int argc, char *argv[])
{
  int i = 0;
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  // INITIALIZATION LOGIC

  int W = 16;
  int array_size = 256;

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
    a[i] = rand()%2;
  }

  //Time Variables
  long long t1, t2, t3;
  long long diff;
  long long time_1, time_2;

  /* MPI Parameters */
  int rank, size, len;
  char name[MPI_MAX_PROCESSOR_NAME];
  int tag = 0;
  double t = 0;
  double localsum = 0;

  //////////////////////////////////////////////////////////////////////
  //////////////////////// START PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////
  MPI_Init(&argc, &argv);                 /* start MPI           */
  //Not really needed, but potentially useful
  MPI_Comm_size(MPI_COMM_WORLD, &size);   /* get number of ranks */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);   /* get rank            */
  MPI_Get_processor_name(name, &len);     /* get run-host name   */
  if (rank == MASTER) {
    int index = 0;
    int active = size - 1;
    MPI_Status status;
    int request_size = 0;
    int failure = -1;
    int all_done = -2;
    bool firstTime = true;
    while (active > 0) {
      MPI_Recv(&request_size, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      if (firstTime) {
          t1 = current_timestamp();
          firstTime = false;
      }
      while (request_size > 0) {
        if (index < array_size){
          MPI_Send(&a[index], 1, MPI_INT, status.MPI_SOURCE, WORK_TAG, MPI_COMM_WORLD);
          request_size = request_size - 1;
          index = index + 1;
        } else {
          MPI_Send(&failure, 1, MPI_INT, status.MPI_SOURCE, WORK_TAG, MPI_COMM_WORLD);
          active = active - 1;
          request_size = 0;
        }
      }
    }
    for (i = 1; i < size; i++) {
      MPI_Send(&all_done, 1, MPI_INT, i, COMPLETE_TAG, MPI_COMM_WORLD);
    }
    t2 = current_timestamp();
    time_1 = t2 - t1;
    printf("Total Time:   %f s\n", ((float)time_1)/1000);
  } else {
    t1 = current_timestamp();
    MPI_Status status;

    int work_queue[W];
    for (i = 0; i < W; i++) { work_queue[i] = 0; }
    bool keep_working = true;

    while (keep_working)
    {
      MPI_Send(&W, 1, MPI_INT, MASTER, WORK_TAG, MPI_COMM_WORLD);
      for (i = 0; i < W; i++)
      {
        MPI_Recv(&work_queue[i], 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if (work_queue[i] == -1)
        {
          i = W + 1;
          t3 = current_timestamp();
          keep_working = false;
        }
      }
      for (i = 0; i < W; i++)
      {
        if (work_queue[i] != -1)
        {
          sleep(work_queue[i]);
        }
      }
    }

    t2 = current_timestamp();
    time_1 = t2 - t1;
    time_2 = t3 - t1;
    int complete_status_message;
    MPI_Recv(&complete_status_message, 1, MPI_INT, MASTER, COMPLETE_TAG, MPI_COMM_WORLD, &status);
    if (complete_status_message != -2) {
      printf("ERORR IN PROCESS %d\n", rank);
    }
    printf("Process %2d -- No More Work Received at %fs -- Work Complete %fs\n", rank, ((float)time_2)/1000, ((float)time_1)/1000);
  }
  MPI_Finalize();                         /* terminate MPI       */
  //////////////////////////////////////////////////////////////////////
  ////////////////////////// END PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////

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
