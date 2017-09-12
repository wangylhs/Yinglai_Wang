#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {

  printf("number of threads in sequential is: %d\n", omp_get_num_threads( ));
  printf("thread number in sequential is: %d\n", omp_get_thread_num( ));

  #pragma omp parallel
  {
     // sub question 1 of A
     #pragma omp single
     printf("number of threads in parallel is: %d\n", omp_get_num_threads( ));

     // sub question 2 of A
     printf("thread number in parallel is: %d\n", omp_get_thread_num( ));

     // sub question 3 of A
     #pragma omp single 
     printf("thread number in single is: %d\n", omp_get_thread_num( ));

     #pragma omp master 
     printf("thread number in master is: %d\n", omp_get_thread_num( ));
   }
}

