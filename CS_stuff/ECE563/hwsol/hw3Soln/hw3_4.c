#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

   omp_set_num_threads(4);

   int i;
   #pragma omp parallel private(i)
   {
      for (i = 0; i < 4; i++) {
         printf("for in par, i = %d, tid = %d\n", i, omp_get_thread_num( ));
      }

      #pragma omp for
      for (i = 0; i < 4; i++) {
         printf("omp for in par, i = %d, tid = %d\n", i, omp_get_thread_num( ));
      }
   }

   #pragma omp parallel for
   for (i = 0; i < 4; i++) {
      printf("for in parfor i = %d\n", i);
      printf("omp parfor, i = %d, tid = %d\n", i, omp_get_thread_num( ));
   }
}
