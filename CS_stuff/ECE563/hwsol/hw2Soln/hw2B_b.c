#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {

   int nt;
   #pragma omp parallel
   #pragma omp single
   nt = omp_get_num_threads( );

   float res[nt*16];
   float a[1000000];

   int i;

   double t = -omp_get_wtime( );

   for (i = 0; i < nt*16; i++) {
      res[i] = 0.0;
   }

   #pragma omp parallel for
   for (i = 0; i < 1000000; i++) {
      a[i] = 1.0/(i+1.);
   }

   #pragma omp parallel 
   {
      int tid = omp_get_thread_num( );
      #pragma omp for
      for (i=0; i < 1000000; i++) {
         res[tid*16] += a[i];
      }
   }

   int tid;
   for (tid = 1; tid < nt; tid++) {
      res[0] += res[tid*16];
   } 

   t += omp_get_wtime( );
   printf("time is: %f2\n", t);
   printf("tot is: %f7\n", res[0]);
}

