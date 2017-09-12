// Nathan Tornquist
// ECE 563 - HW5
// Nathan Tornquist
//
// This is the sample Hello World program from rcac.purdue.edu
// This has been modified and configured by Nathan Tornquist
// Compile the program: 
// mpicc hw5.c -o hw5
//
// Execute the program:
// qsub -l nodes=2:ppn=16,walltime=00:01:00 ./hw5.sub

#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[]) {

    /* MPI Parameters */
    int rank, size, len;
    char name[MPI_MAX_PROCESSOR_NAME];

    /* All ranks initiate the message-passing environment. */
    /* Each rank obtains information about itself and its environment. */
    MPI_Init(&argc, &argv);                 /* start MPI           */
    MPI_Comm_size(MPI_COMM_WORLD, &size);   /* get number of ranks */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   /* get rank            */
    MPI_Get_processor_name(name, &len);     /* get run-host name   */

    printf("Hello World -- %s (%d/%d)\n", name,rank,size);

    MPI_Finalize();                         /* terminate MPI       */
    return 0;
}
