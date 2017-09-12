/******************************************************************************
* FILE: mm_opm.c
* DESCRIPTION:
*   OpenMP Matrix Multiply
*   This program will generate two large matrices then multiply them using
*   multiple cores.  The program will compare the result to a proven
*   algorithm so that correctness can be analyzed, and with a correct solution,
*   speedup can be considered.
* AUTHOR: Nathan Tornquist 2/15
* LAST REVISED: 02/04/15
*
* On OSX:
* g++-4.9 -o mm_omp -fopenmp mm_omp.c
*
* On ecegrid:
* gcc -o mm_omp -fopenmp mm_omp.c -std=c99
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void printMatrix(double **mat, int width, int height);
void makeMatrixRows(double** mat, int height, int width, bool zero);
long long current_timestamp();

int main (int argc, char *argv[])
{
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  // INITIALIZATION LOGIC

  int cores = 16;
  int m = 900;
  int n = 900;
  int o = 900;

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

  omp_set_dynamic(0);     // Disable Dynamic Threads
  omp_set_num_threads(cores); // Set Num Threads (change for benchmarking)

  // Initialize a, b, and c matrices
  int seed = time(NULL);
  srand(seed);

  printf("Generating a %dx%d matrix and a %dx%d matrix.\n",m,n,n,o);
  double *a[m];
  makeMatrixRows(a, m, n, false);
  double *b[n];
  makeMatrixRows(b, n, o, false);
  double *c[m];
  makeMatrixRows(c, m, o, true);
  double *d[m];
  makeMatrixRows(d, m, o, true);

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
  #pragma omp parallel shared(a,b) private(row, col, off)
  {
    #pragma omp for schedule(static)
    for (int row = 0; row < m; row++) {
      for (int col = 0; col < o; col++) {
        int sum = 0;
        for (int off = 0; off < n; off++) {
          sum += a[row][off] * b[off][col];
        }
        c[row][col] = sum;
      }
    }
  }
  //////////////////////////////////////////////////////////////////////
  ////////////////////////// END PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////
  t2 = current_timestamp();
  time_1 = t2 - t1;

  printf("Multiplication Completed\n");
  printf("Generating Solution for Verification\n");

  t1 = current_timestamp();
  for (int row = 0; row < m; row++) {
    for (int col = 0; col < o; col++) {
      for (int off = 0; off < n; off++) {
        d[row][col] += a[row][off] * b[off][col];
      }
    }
  }
  t2 = current_timestamp();
  time_2 = t2 - t1;

  //VERIFY SOLUTION
  printf("Verifying Solution\n\n");

  int miss = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < o; j++) {
      if (c[i][j] != d[i][j]) miss++;
    }
  }
  printf("Results:\n");
  if (miss != 0) {
    printf("Solution: Invalid\n");

    if (m < 10 && o < 10){
      printf("A: \n");
      printMatrix(a,m,n);
      printf("\nB: \n");
      printMatrix(b,n,o);
      printf("\nParallel Out: \n");
      printMatrix(c,m,o);
      printf("\nSolution: \n");
      printMatrix(d,m,o);
    }
  }
  else {
    printf("Solution: Valid\n");
    printf("Parallel:   %f s\n", ((float)time_1)/1000);;
    printf("Sequential: %f s\n", ((float)time_2)/1000);;
    printf("Speedup: %.2f %%\n", (100*((float)time_2)/((float)time_1)));
    printf("Cores: %d\n", cores);
  }

  //Free memory
  for (int i = 0; i < m; i++)
  {
    free(a[i]);
    free(c[i]);
    free(d[i]);
  }
  for (int i = 0; i < n; i++)
  {
    free(b[i]);
  }
}

void printMatrix(double **mat, int height, int width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      printf("%9.0f ",mat[i][j]);
    }
    printf("\n");
  }
}

void makeMatrixRows(double** mat, int height, int width, bool zero) {
  for (int i = 0; i < height; i++) {
    mat[i] = (double *)malloc(width * sizeof(double));
    for (int j = 0; j < width; j++) {
      if (zero)
        mat[i][j] = 0;
      else
        mat[i][j] = rand()%100;
    }
  }
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
