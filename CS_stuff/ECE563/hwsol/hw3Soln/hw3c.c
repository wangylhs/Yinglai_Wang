#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {

  int i; 
  int tid;
  printf("before parfor tid: %d, tid address: %p\n",tid, (void*) &tid); 
  omp_set_num_threads(4);
  #pragma omp parallel for 
  for (i=0; i < omp_get_num_threads( ); i++) {
     /* Obtain thread number */
     tid = omp_get_thread_num();

     #pragma omp critical 
     printf("tid: %d, tid address: %p\n",tid, (void*) &tid); 
  }  /* All threads join master thread and disband */
  printf("after parfor tid: %d, tid address: %p\n",tid, (void*) &tid); 
}

