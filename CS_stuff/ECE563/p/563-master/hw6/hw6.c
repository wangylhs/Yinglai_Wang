// Nathan Tornquist
// ECE 563
// HW 6
//
// Usage:
//  Respond to the program prompts to calculate
//  what regions of a given range of data will
//  be assigned to each processor core.

#include <stdio.h>

int main (int argc, char *argv[]) {
  int p, d;

  printf("Cyclic Block Scheduling Tool\n");
  printf("Enter Number of Processors:\n");
  scanf("%d", &p);
  printf("Enter Array Size:\n");
  scanf("%d", &d);

  printf("\nResults:\n");

  int i = 0;
  for (i = 0; i < p; i++)
  {
    printf("%d: ",i);
    if (i < d) {
      int j = i;
      printf("[%d:",i);
      while (j < d) {
        j = j + p;
      }
      j = j - p;
      printf("%d:%d]",j,p);
    } else {
      printf("[N\\A]");
    }
    printf("\n");
  }
  return 0;
}
