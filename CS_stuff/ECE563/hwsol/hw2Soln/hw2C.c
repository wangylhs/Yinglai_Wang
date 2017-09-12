#include <stdio.h>

void twoSums(int ub) {
   float tot1, tot2;
   int i;

   tot1 = tot2 = 0;
   for (i = 1; i < ub; i++) {
      tot1 = tot1 + 1.0/i;
   }
   printf("size: %d, tot1: %.6f\n", ub, tot1);

   for (i = ub; i > 0;  i--) {
      tot2 = tot2 + 1.0/i;
   }
   printf("size: %d, tot2: %.6f\n", ub, tot2);
}

int main( ) {
   twoSums(1000000); 
   twoSums(10000000); 
}
