#include <stdio.h>
#include <time.h>

int main( ) {
   double a[1000000];
   clock_t s= -clock();
   int i;
   for (i = 0; i < 1000000; i++) {
      a[i] = 1.0/i;
   }

   double res = 0;
   for (i = 0; i < 1000000; i++) {
      res += a[i];
   }
   s += clock(); 
   int msec = s*1000/CLOCKS_PER_SEC;
   printf("time taken, %d seconds, %d milliseconds\n", msec/100, msec%1000);
}
