#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Q {
   int* q;
   int pos;
   int size;
} Q;

struct Q* initQ(int n) {
   struct Q *newQ = (struct Q *) malloc(sizeof(Q));   
   newQ->q = (int*) malloc(sizeof(int)*n);
   newQ->pos = -1;
   newQ->size = n-1;
}

int printQStatus(struct Q* workQ) {
   printf("Q Status\n");
   printf("q: %p\n", (void *) workQ->q);
   printf("pos: %d\n", workQ->pos);
   printf("size: %d\n\n", workQ->size);
}

void putWork(struct Q* workQ) {
   if (workQ->pos < (workQ->size)) {
      workQ->pos++;
      workQ->q[workQ->pos] = (int) (rand( )%2*(workQ->pos/1000));
   } else printf("ERROR: attempt to add Q element%d\n", workQ->pos+1);
}

int getWork(struct Q* workQ, int* work) {
   int rc;
   #pragma omp critical
   {
      if (workQ->pos > -1) {
         *work = workQ->q[workQ->pos];
         workQ->pos--;
         rc = 1;
      } else {
         rc = 0;
      }
   }
   return rc;
}

int main (int argc, char *argv[]) {
   
   const int SIZE = 1000;
   const int SEQ = 0;
   const int PAR = 1;
   struct Q* wQ = initQ(SIZE);
   int i;

   printf("before sequential\n");
   printQStatus(wQ);
   for (i = 0; i < SIZE; i++) {
      putWork(wQ);
   }
   printf("after sequential build\n");
   printQStatus(wQ);

   double s[2];
   int work;

   s[SEQ] = -omp_get_wtime( );
   while (getWork(wQ, &work)) {
      usleep(work*1000);
   }
   s[SEQ] += omp_get_wtime( );
   printf("after sequential work\n");
   printQStatus(wQ);

   for (i = 0; i < SIZE; i++) {
      putWork(wQ);
   }
   printf("after parallel build\n");
   printQStatus(wQ);

   omp_set_num_threads(4);

   s[PAR] = -omp_get_wtime( );
   #pragma omp parallel 
   {
      int status;

      status = getWork(wQ,&work);

      while (status) {
         usleep(work*1000);

         status = getWork(wQ, &work);

         usleep(work*1000);
      }
   }
   s[PAR] += omp_get_wtime( );

   printf("\ntimes:\n");
   printf("sequential %d s, %d ms\n", sec(s[SEQ]), ms(s[SEQ]));
   printf("parallel %d s, %d ms\n", sec(s[PAR]), ms(s[PAR]));
}
