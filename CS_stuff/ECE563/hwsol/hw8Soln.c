#include	<stdio.h>
#include	<mpi.h>

int min(int a1, int a2) {
   if (a1 < a2) return a1; else return a2;
}

int main(int argc, char* argv[ ]) {

   int numProc, pid;
   int globalUB;
   float *a, t, red;
   double etime;

   // block information
   int blockLB; 
   int blockUB; 
   int localBS;
   int i, several;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numProc);
   MPI_Comm_rank(MPI_COMM_WORLD, &pid);

   a = 0;
   for (globalUB = 10000; globalUB < 1000000+1; globalUB = globalUB*10) {

      // compute block distribution parameters
      blockLB = pid*globalUB/numProc;
      blockUB = min(globalUB, (pid+1)*globalUB/numProc - 1);
      localBS = blockUB - blockLB + 1; 
      if (a != 0) free(a);
      a = (float *) malloc(sizeof(float)*(localBS));

      for (i = 0; i < localBS; i++) {
         a[i] = 1.0;
      }

      printf("\nblock: %d, on processor %d, the local bounds are [%d:%d], and the global bounds are [%d:%d]", numProc, pid, 0, localBS, blockLB, blockUB); 

      // do the MPI reduction operation version
      etime = -MPI_Wtime( );
      for (several = 0; several < 5; several++) { 
         for (i = 0; i < localBS; i++) {
            t += a[i];
         }
         MPI_Allreduce(&t, &red, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD); 
      }
      etime += MPI_Wtime( );
      printf("\nElapsed time, %d elements took %E seconds, reduction is %E", globalUB, etime, t); 

      // do the manual reduction version.
      for (several = 0; several < 5; several++) { 
         double t1;
         int sender, span;
         MPI_Status status;
         etime = -MPI_Wtime( );
         for (i = 0; i < localBS; i++) {
            t += a[i];
         }
         // only works for power of two processors
         for (span = 2; span < numProc; span *= 2) {
            int halfspan = span / 2;
            int modu = pid % span;
            if (modu % span == 0) { 
               MPI_Recv(&t1, 1, MPI_FLOAT, span+halfspan, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
               t = t + t1;
            }
            if (modu % span == halfspan) { 
               MPI_Send(&t, 1, MPI_FLOAT, pid-halfspan, MPI_ANY_TAG, MPI_COMM_WORLD);
            }
         }
         etime += MPI_Wtime( );
         if (pid == 0) {
            printf("\nManual elapsed time, %d elements took %E seconds, reduction is %E", globalUB, etime, t); 
           
         }
      }
   }
   MPI_Finalize();

   return 0;
}
