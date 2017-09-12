/******************************************************************************
* FILE: mm_mpi.c
* DESCRIPTION:
*   MPI Matrix Multiply
*   This program will generate two large matrices then multiply them using
*   multiple cores.  The program will compare the result to a proven
*   algorithm so that correctness can be analyzed, and with a correct solution,
*   speedup can be considered.
* AUTHOR: Nathan Tornquist 3/19
* LAST REVISED: 03/22/15
*
* Compile the program:
* mpicc mm_mpi.c -o mm_mpi
*
* Execute the program:
* qsub -l nodes=1:ppn=16,walltime=00:01:00 ./mm_mpi.sub
******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

long long current_timestamp();

#define m 1500
#define n 1500
#define o 1500

double a[m][n];
double b[n][o];
double c[m][o];
double d[m][o];

int main (int argc, char *argv[])
{
  /* MPI Parameters */
  int rank, size, len;
  MPI_Init(&argc, &argv);                 /* start MPI           */
  MPI_Comm_size(MPI_COMM_WORLD, &size);   /* get number of ranks */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);   /* get rank            */

  MPI_Request request[32];
  MPI_Status status[32];
  int i, j = 0;

  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  //Note for above variables:
  //
  //       __(n)__        ____(o)____
  //    m |       |    n |           |
  //      |_______|      |           |
  //                     |___________|
  //
  //   makes:
  //
  //          ____(o)____
  //     m   |           |
  //         |___________|
  //
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  int step_size = m / size;
  int extra = m % size;

  if (rank == 0) {
    printf("/////////////////////////////////////////////////////////////////\n");
    printf("/////////////////////////////////////////////////////////////////\n");
    printf("/////////////////////////////////////////////////////////////////\n");
    int seed = time(NULL);
    srand(seed);
    printf("Generating a %dx%d matrix and a %dx%d matrix.\n",m,n,n,o);
    //makeMatrixRows(a, m, n, false);
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
        a[i][j] = rand()%100;
      }
    }
    //makeMatrixRows(b, n, o, false);
    for (i = 0; i < m; i++) {
      for (j = 0; j < o; j++) {
        b[i][j] = rand()%100;
      }
    }
    //makeMatrixRows(c, m, o, true);
    //makeMatrixRows(d, m, o, true);

    //Time Variables
    long long t1, t2;
    long long diff;
    long long time_1, time_2;


    printf("Starting Parallel Operation\n");
    t1 = current_timestamp();

    //////////////////////////////////////////////////////////////////////
    //////////////////////// START PARALLEL LOGIC ////////////////////////
    //////////////////////////////////////////////////////////////////////
    MPI_Bcast(a, m*n, MPI_DOUBLE, 0, MPI_COMM_WORLD); // send broadcast
    MPI_Bcast(b, n*o, MPI_DOUBLE, 0, MPI_COMM_WORLD); // send broadcast
    int row, col, off;
    for (row = 0; row < step_size + extra; row++) {
      for (col = 0; col < o; col++) {
        for (off = 0; off < n; off++) {
          c[row][col] += a[row][off] * b[off][col];
        }
      }
    }
    for(i = 1; i < size; i++) {
      MPI_Irecv(c + (step_size*i + extra), step_size*o, MPI_DOUBLE, i, i, MPI_COMM_WORLD, request+i-1);
    }
    MPI_Waitall(size-1, request, status);
    //////////////////////////////////////////////////////////////////////
    ////////////////////////// END PARALLEL LOGIC ////////////////////////
    //////////////////////////////////////////////////////////////////////
    t2 = current_timestamp();
    time_1 = t2 - t1;

    printf("Multiplication Completed\n");
    printf("Generating Solution for Verification\n");

    t1 = current_timestamp();
    for (row = 0; row < m; row++) {
      for (col = 0; col < o; col++) {
        for (off = 0; off < n; off++) {
          d[row][col] += a[row][off] * b[off][col];
        }
      }
    }
    t2 = current_timestamp();
    time_2 = t2 - t1;

    //VERIFY SOLUTION
    printf("Verifying Solution\n\n");

    int miss = 0;
    for (i = 0; i < m; i++) {
      for (j = 0; j < o; j++) {
        if (c[i][j] != d[i][j]) miss++;
      }
    }
    printf("Results:\n");
    if (miss != 0) {
      printf("Solution: Invalid\n");
    }
    else {
      printf("Solution: Valid\n");
      printf("Parallel:   %f s\n", ((float)time_1)/1000);;
      printf("Sequential: %f s\n", ((float)time_2)/1000);;
      printf("Speedup: %.2f %%\n", (100*((float)time_2)/((float)time_1)));
      printf("Threads: %d\n", size);
    }
  }
  else
  {
    MPI_Bcast(a, m*n, MPI_DOUBLE, 0, MPI_COMM_WORLD); // receive broadcast
    MPI_Bcast(b, n*o, MPI_DOUBLE, 0, MPI_COMM_WORLD); // receive broadcast
    int row, col, off;
    for (row = (step_size*rank + extra); row < step_size*(rank+1) + extra; row++) {
      for (col = 0; col < o; col++) {
        for (off = 0; off < n; off++) {
          c[row][col] += a[row][off] * b[off][col];
        }
      }
    }
    MPI_Send(c+(step_size*rank + extra), step_size*o, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
  }

  MPI_Finalize();                         /* terminate MPI       */
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
