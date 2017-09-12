#include <stdio.h>
#include <string.h> // this allows us to manipulate text strings
#include "mpi.h" // this adds the MPI header files to the program

int main(int argc, char* argv[]) {
   int my_rank; 
   int p;
   int source; 
   int dest;
   int tag = 0;
   char message[100]; // storage for message
   MPI_Status status; // stores status for MPI_Recv statements
   
   // starts up MPI
   MPI_Init(&argc, &argv);
   
   // finds out rank of each process 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
   
   // finds out number of processes 
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   if (my_rank != 0) {
      sprintf(message, "Greetings from process %d!", my_rank);
      dest = 0; // sets destination for MPI_Send to process 0
      // sends the string to process 0
      MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
   } else {
      for(source = 1; source < p; source++){
         // receives greeting from each process
         MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
         printf("%s\n", message); // prints out greeting to screen
         fflush(stdout);
      } 
   }
   MPI_Finalize(); // shuts down MPI
   return 0; 
}
