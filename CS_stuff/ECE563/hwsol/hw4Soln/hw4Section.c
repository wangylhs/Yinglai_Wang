#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void doWork(int t) {
   usleep(t*10000);
}

int* initWork(int n) {
   int i;
   double r;
   int* wA = (int *) malloc(sizeof(int)*n);   
   for (i = 0; i < n; i++) {
      wA[i] = (int) rand( )%2*i/(n/10);
   }
   return wA;
}

int main (int argc, char *argv[]) {
   int i;
   const int SIZE = 1000;
   const int T = 4;
   const int SEQ = 0;
   const int SECT = 1;

   double s[2];

   int *w = initWork(SIZE);
   for (i = 0; i < SIZE; i+=500) {
      printf("w[%d] = %d\n", i, w[i]);
   }

   omp_set_num_threads(T);

   s[SEQ] = -omp_get_wtime( );
   for (i = 0; i < SIZE; i++) {
      doWork(w[i]);   
   }
   s[SEQ] += omp_get_wtime();

   s[SECT] = -omp_get_wtime( );
   #pragma omp parallel sections
   {
      #pragma omp section
      {
         int i;
         for (i = omp_get_thread_num( ); i < SIZE; i+=T) {
            doWork(w[i]);
         }
      }
      #pragma omp section
      {
         int i;
         for (i = omp_get_thread_num( ); i < SIZE; i+=T) {
            doWork(w[i]);
         }
      }
      #pragma omp section
      {
         int i;
         for (i = omp_get_thread_num( ); i < SIZE; i+=T) {
            doWork(w[i]);
         }
      }
      #pragma omp section
      {
         int i;
         for (i = omp_get_thread_num( ); i < SIZE; i+=T) {
            doWork(w[i]);
         }
      }
   }
   s[SECT] += omp_get_wtime();

   printf("\ntimes:\n");
   printf("sequential %2f\n", s[SEQ]);
   printf("sections %2f\n", s[SECT]);
}

