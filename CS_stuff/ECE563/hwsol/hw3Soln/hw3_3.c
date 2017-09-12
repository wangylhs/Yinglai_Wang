#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int sumRed(int a[], int len) {
   int res = 0;
   int i;
   for (i = 0; i < len; i++) {
      res += a[i];
   }
   return res;
}

int main (int argc, char *argv[]) {

   omp_set_num_threads(4);

   int size = 1000000;
   int a[size], b[size];
   int res[2] = {0, 0};
   int i;


   for (i = 0; i < size; i++) {
      a[i] = b[i] = 0;
   }

   #pragma omp parallel sections
   {
      #pragma omp section
      res[0] = sumRed(a, size);
      #pragma omp section
      res[1] = sumRed(b, size);
   }
}
