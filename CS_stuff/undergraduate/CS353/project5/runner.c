#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 51
#define MASTER 0
int crashData[MAX];
void crashReport();
int main(int argc, char** argv){
    //initialize crashData
    int i;
    for(i=0; i<MAX; i++) crashData[i] = 0;
    //define the run command
    char run[128];
    strcpy(run, "./run.sh ./");
    char* name = strdup("sample2");
    strcat(run, name);
    //create the trace file
    FILE *data0 = fopen("curr.txt", "w");
    fputs("-1\n", data0);
    fclose(data0);
    
    
    int numtasks, taskid, len, sender, recv;
    MPI_Status pstatus;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
    MPI_Get_processor_name(hostname, &len);
    if(taskid == MASTER){
        for(i=1; i<numtasks; i++){
            MPI_Recv(&recv, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &pstatus);
            crashData[i] = recv;
            //fprintf(stderr, "recv is:----------------%d\n", recv);
        }
        crashReport();
        
    }else{
        //fprintf(stdout, "Process %d start\n", taskid);
        int status = system(run);
        if(status!=0){
            crashData[taskid] = taskid;
        }
        //fprintf(stderr, "status is:-----------%d\n", status);
        MPI_Send(&crashData[taskid], 1, MPI_INT, MASTER, 2, MPI_COMM_WORLD);
        FILE *data1 = fopen("curr.txt", "w");
        fprintf(data1, "%d\n", i + 1);
        fclose(data1);
        fprintf(stdout, "Process %d finish.\n", taskid);
    }
    
    MPI_Finalize();
    
}

void crashReport(){
    int flag = 0;
    fprintf(stderr, "========== Crash Report Start ==========\n");
    int i;
    for(i=1; i<MAX; i++){
        if(crashData[i]!=0){
            flag++;
            fprintf(stderr, "Crash ocurred at synchronization point %d/%d\n", crashData[i],MAX);
        }
    }
    if(flag==0) fprintf(stderr, "No crash ocurred.\n");
    fprintf(stderr, "========== Crash Report End ==========\n");
}