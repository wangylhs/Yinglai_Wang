#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void doWork(int t) {
   usleep(t*10000);
}

int* initWork(int n) {
   int i;
   double r;
   int* wA = (int *) malloc(sizeof(int)*n);   
   for (i = 0; i < n; i++) {
      wA[i] = rand( )%2*i/(n/2);
   }
   return wA;
}

int main (int argc, char *argv[]) {
   int i;
   const int SIZE = 10000;
   const int STATIC = 0;
   const int STATIC50 = 1;
   const int DYNAMIC = 2;
   const int DYNAMIC50 = 3;
   const int GUIDED = 4;

   double s[5];


   int *w = initWork(SIZE);
   for (i = 0; i < SIZE; i+=500) {
      printf("w[%d] = %d\n", i, w[i]);
   }

   omp_set_num_threads(16);

   s[STATIC] = -omp_get_wtime( );
   #pragma omp parallel for 
   for (i = 0; i < SIZE; i++) {
      doWork(w[i]);
   }
   s[STATIC] += omp_get_wtime();

   s[STATIC50] = -omp_get_wtime();
   #pragma omp parallel for schedule(static,50)
   for (i = 0; i < SIZE; i++) {
      doWork(w[i]);
   }
   s[STATIC50] += omp_get_wtime();

   s[DYNAMIC] = -omp_get_wtime();
   #pragma omp parallel for schedule(dynamic)
   for (i = 0; i < SIZE; i++) {
      doWork(w[i]);
   }
   s[DYNAMIC] += omp_get_wtime();

   s[DYNAMIC50] = -omp_get_wtime();
   #pragma omp parallel for schedule(dynamic,50)
   for (i = 0; i < SIZE; i++) {
      doWork(w[i]);
   }
   s[DYNAMIC50] += omp_get_wtime();

   s[GUIDED] = -omp_get_wtime();
   #pragma omp parallel for schedule(guided)
   for (i = 0; i < SIZE; i++) {
      doWork(w[i]);
   }
   s[GUIDED] += omp_get_wtime();

   printf("times:\n\n");
   printf("static %2f s\n", s[STATIC]);
   printf("static50 %2f s\n", s[STATIC50]);
   printf("dynamic %2f s\n", s[DYNAMIC]);
   printf("dynamic50 %2f s\n", s[DYNAMIC50]);
   printf("guided %2f s\n", s[GUIDED]);
}

