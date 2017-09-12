/******************************************************************************
* FILE: mm_mpi_2.c
* DESCRIPTION:
*   MPI Matrix Multiply
*   This program will generate two large matrices then multiply them using
*   multiple cores.  The program will compare the result to a proven
*   algorithm so that correctness can be analyzed, and with a correct solution,
*   speedup can be considered.
*
*   This program gains its main optimizations through the way matrixes are
*   being stored.  a is a normal matrix, while b is stored as the transpose.
*   You can see that distinction in the way the matrix multiply is computed.
*
*   This drastically simplifies the communication model.
*
* AUTHOR: Nathan Tornquist 3/19
* LAST REVISED: 04/19/15
*
* Compile the program:
* mpicc mm_mpi_2.c -o mm_mpi_2
*
* Execute the program:
* qsub -l nodes=1:ppn=16,walltime=00:01:00 ./mm_mpi_2.sub
******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

long long current_timestamp();

//1536 is a good number (divides evenly between 1, 2, 4, 8, 16, 32)
#define m 1536
#define n 1536
#define o 1536

double a[m][n];
double b[n][o];
double c[m][o];
double d[m][o];

//Multiples a range of a * b and places in c.
void multiply_range(int startA, int endA, int startB, int endB) {
  int row, col, off;
  for (row = startA; row < endA; row++) {
    for (col = startB; col < endB; col++) {
      for (off = 0; off < n; off++) {
        c[row][col] += a[row][off] * b[col][off];
      }
    }
  }
}

void print(int choice) {
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < o; j++) {
      if (choice == 0) {
        printf("%08f ",a[i][j]);
      } else if (choice == 1) {
        printf("%08f ",b[i][j]);
      } else if (choice == 2) {
        printf("%08f ",c[i][j]);
      }
    }
    printf("\n");
  }
}

int main (int argc, char *argv[])
{
  /* MPI Parameters */
  int rank, size, len;
  MPI_Init(&argc, &argv);                 /* start MPI           */
  MPI_Comm_size(MPI_COMM_WORLD, &size);   /* get number of ranks */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);   /* get rank            */

  MPI_Request request[32];
  MPI_Status status;
  int i, j, k = 0;
  int row, col, off;

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
  //int extra = m % size;

  //Time Variables
  long long t1, t2;
  long long diff;
  long long time_1, time_2;

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

    printf("Starting Parallel Operation\n");
    t1 = current_timestamp();
  }

  //////////////////////////////////////////////////////////////////////
  //////////////////////// START PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////

  //Initial Distribution of Blocks
  if (rank == 0) {
    for (i = 1; i < size; i++) {
      MPI_Send(a + step_size*i, step_size*o, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
    }
    for (i = 1; i < size; i++) {
      MPI_Send(b + step_size*i, step_size*o, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
    }
  } else {
    MPI_Recv(a + step_size*rank, step_size*o, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD, &status);
    MPI_Recv(b + step_size*rank, step_size*o, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD, &status);
  }

  i = 0;
  while (i < size) {
    j = (size-i+rank)%size;
    k = (size-i+rank-1)%size;

    //printf("%d : %d : %d : %d\n", rank, i, j*step_size, (j+1)*step_size);

    //Multiply with current block
    multiply_range(rank*step_size, (rank+1)*step_size, j*step_size, (j+1)*step_size);

    //Share blocks
    if (rank%2 == 0) {
      MPI_Send(b + step_size*j, step_size*o, MPI_DOUBLE, (rank+1)%size, 0, MPI_COMM_WORLD);
      MPI_Recv(b + step_size*k, step_size*o, MPI_DOUBLE, (rank-1)%size, 0, MPI_COMM_WORLD, &status);
    } else {
      MPI_Recv(b + step_size*k, step_size*o, MPI_DOUBLE, (rank-1)%size, 0, MPI_COMM_WORLD, &status);
      MPI_Send(b + step_size*j, step_size*o, MPI_DOUBLE, (rank+1)%size, 0, MPI_COMM_WORLD);
    }
    i++;
  }

  MPI_Allreduce(MPI_IN_PLACE,c,m*o,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);

  //////////////////////////////////////////////////////////////////////
  ////////////////////////// END PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////
  if (rank == 0) {
    t2 = current_timestamp();
    time_1 = t2 - t1;

    printf("Multiplication Completed\n");
    printf("Generating Solution for Verification\n");

    t1 = current_timestamp();
    for (row = 0; row < m; row++) {
      for (col = 0; col < o; col++) {
        for (off = 0; off < n; off++) {
          d[row][col] += a[row][off] * b[col][off];
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
