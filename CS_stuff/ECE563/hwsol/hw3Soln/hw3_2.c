#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {

   omp_set_num_threads(4);

   // program for critical
   #pragma omp parallel 
   #pragma omp critical
   printf("crit tid: %d\n", omp_get_thread_num( ));

   // program for master
   #pragma omp parallel 
   #pragma omp master
   printf("master tid: %d\n", omp_get_thread_num( ));

   // program for single
   #pragma omp single
   printf("single tid: %d\n", omp_get_thread_num( ));
}

