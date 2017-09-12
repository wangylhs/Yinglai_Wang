#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {

   int nt;
   #pragma omp parallel
   #pragma omp single
   nt = omp_get_num_threads( );

   float res;
   float a[1000000];

   int i;

   double t = -omp_get_wtime( );

   res = 0.0;

   #pragma omp parallel for
   for (i = 0; i < 1000000; i++) {
      a[i] = 1.0/(i+1.);
   }

   #pragma omp parallel for reduction(+:res)
   for (i=0; i < 1000000; i++) {
      res += a[i];
   }

   t += omp_get_wtime( );
   printf("time is: %f2\n", t);
   printf("tot is: %f7\n", res);
}

