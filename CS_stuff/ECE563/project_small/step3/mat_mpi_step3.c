/* Yinglai Wang */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

#define seq 11.903415

void mat_mul(int m, int n, int p, int** mat_1, int** mat_2, int** mat_3){
    int i,j,k;
    for (i=0; i<m; i++){
        for (j=0; j<n; j++){
            for (k=0; k<p; k++){
                mat_3[i][j] += mat_1[i][k]*mat_2[k][j];
            }
        }
    }
}

void print_mat(int** mat, int rows, int col){
    int i,j;
    
    for(i=0;i<rows;i++){
        for(j=0;j<col;j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int **allocate_mat(int row, int col){
    int **result;
    int i;
    result = (int **)malloc(sizeof(int *)*row);
    result[0] = (int *)malloc(sizeof(int)*row*col);
    for(i=1;i<row;i++){
        result[i]=result[i-1]+col;
    }
    return result;
}

void init_matrix(int **mat,int size){
    int ct = 0;
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            mat[i][j] = ct%9;
            ct++;
        }
    }
}

int is_diagonal(int pid, int* half_pid, int len){
    int i;
    for(i=0;i<len;i++){
        if(pid==half_pid[i]) return 1;
    }
    return 0;
}

void init_half_pid(int** pid_array, int* half_pid, int p_sqrt){
    int ct=0;
    int i,j;
    for(i=0;i<p_sqrt;i++){
        if(i%2==0){
            for(j=0;j<p_sqrt;j++){
                if(pid_array[i][j]%2==0){
                    half_pid[ct]=pid_array[i][j];
                    ct++;
                }
            }
        }
        if(i%2==1){
            for(j=0;j<p_sqrt;j++){
                if(pid_array[i][j]%2==1){
                    half_pid[ct]=pid_array[i][j];
                    ct++;
                }
            }
        }
    }
}

int get_col_index(int pid, int** pid_array, int p_sqrt){
    int i,j;
    for(i=0;i<p_sqrt;i++){
        for(j=0;j<p_sqrt;j++){
            if(pid==pid_array[i][j]) return j;
        }
    }
    return 0;
}
int get_row_index(int pid, int** pid_array, int p_sqrt){
    int i,j;
    for(i=0;i<p_sqrt;i++){
        for(j=0;j<p_sqrt;j++){
            if(pid==pid_array[i][j]) return i;
        }
    }
    return 0;
}

int main(int argc, char * argv[]){
    int **mat_A, **mat_B, **mat_C;
	int **sub_A, **sub_B, **sub_C;
    int **new_sub_A, **new_sub_B;
	int i,j,k;
	int pid;
	int num_proc;
	int size = 1024;
	int row, col;
    double begin, end;
	
	
	MPI_Status status;
	MPI_Init ( &argc, &argv );
    MPI_Comm_size ( MPI_COMM_WORLD, &num_proc );  
    MPI_Comm_rank ( MPI_COMM_WORLD, &pid );
    MPI_Datatype block, blocktype;
    int p_sqrt = sqrt(num_proc);
    int *displ=malloc(sizeof(int)*num_proc);
    int *scount=malloc(sizeof(int)*num_proc);;
    int sub_size = size*size/num_proc;
    int rcount = sub_size;
    
    MPI_Type_vector(size/p_sqrt,size/p_sqrt,size,MPI_INT, &block);
    MPI_Type_commit(&block);
    MPI_Type_create_resized(block,0,(size/p_sqrt)*sizeof(int),&blocktype);
    MPI_Type_commit(&blocktype);
    //initialize scount, displ and pid array
    for(i=0;i<num_proc;i++) scount[i]=1;
    int ct=0;
    for(i=0;i<p_sqrt;i++){
        for(j=0;j<p_sqrt;j++){
            displ[ct]= j + i*size;
            ct++;
        }
    }
    ct=0;
    int **pid_array = allocate_mat(p_sqrt,p_sqrt);
    int *half_pid = malloc(sizeof(int)*num_proc/2);
    for(i=0;i<p_sqrt;i++){
        for(j=0;j<p_sqrt;j++){
            pid_array[i][j] = ct;
            ct++;
        }
    }
    init_half_pid(pid_array,half_pid,p_sqrt);
    
    mat_A = allocate_mat(size,size);
    mat_B = allocate_mat(size,size);
    mat_C = allocate_mat(size,size);
    if(pid==0){
        init_matrix(mat_A,size);
        init_matrix(mat_B,size);
        begin = MPI_Wtime();
        //print_mat(mat_B,6,6);
    }

    sub_A = allocate_mat(size/p_sqrt,size/p_sqrt);
    sub_B = allocate_mat(size/p_sqrt,size/p_sqrt);
    new_sub_A = allocate_mat(size/p_sqrt,size/p_sqrt);
    new_sub_B = allocate_mat(size/p_sqrt,size/p_sqrt);
    sub_C = allocate_mat(size/p_sqrt,size/p_sqrt);
    //initialize sub_C
    for(i=0;i<size/p_sqrt;i++){
        for(j=0;j<size/p_sqrt;j++) sub_C[i][j]=0;
    }
    
    MPI_Scatterv(*mat_A,scount,displ,blocktype,*sub_A,rcount,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatterv(*mat_B,scount,displ,blocktype,*sub_B,rcount,MPI_INT,0,MPI_COMM_WORLD);
    
    //rearrange blocks for mat_A
    int src_A = pid+1;
    int dest_A = pid-1;
    if(src_A>pid_array[pid/p_sqrt][p_sqrt-1]) src_A=pid_array[pid/p_sqrt][0];
    if(dest_A<pid_array[pid/p_sqrt][0]) dest_A=pid_array[pid/p_sqrt][p_sqrt-1];
    
    
    if(get_col_index(pid,pid_array,p_sqrt)%2==0){
        for(i=0;i<pid/p_sqrt;i++){
            
            MPI_Send(*sub_A,sub_size,MPI_INT,dest_A,1,MPI_COMM_WORLD);
            MPI_Recv(*sub_A,sub_size,MPI_INT,src_A,1,MPI_COMM_WORLD,&status);
            //if(pid==10) print_mat(sub_A,2,2);
        }
    }else{
        for(i=0;i<pid/p_sqrt;i++){
            MPI_Recv(*new_sub_A,sub_size,MPI_INT,src_A,1,MPI_COMM_WORLD,&status);
            MPI_Send(*sub_A,sub_size,MPI_INT,dest_A,1,MPI_COMM_WORLD);
            /*if(pid==11){
                print_mat(new_sub_A,2,2);
                print_mat(sub_A,2,2);
            }*/
            for(j=0;j<size/p_sqrt;j++){
                for(k=0;k<size/p_sqrt;k++) sub_A[j][k]=new_sub_A[j][k];
            }
        }
    }
    
    
    //rearrange blocks for mat_B
    int src_B = pid+p_sqrt;
    int dest_B = pid-p_sqrt;
    if(src_B>pid_array[p_sqrt-1][pid%p_sqrt]) src_B=pid_array[0][pid%p_sqrt];
    if(dest_B<pid_array[0][pid%p_sqrt]) dest_B=pid_array[p_sqrt-1][pid%p_sqrt];
    
    if(get_row_index(pid,pid_array,p_sqrt)%2==0){
        for(i=0;i<pid%p_sqrt;i++){
            MPI_Send(*sub_B,sub_size,MPI_INT,dest_B,1,MPI_COMM_WORLD);
            MPI_Recv(*sub_B,sub_size,MPI_INT,src_B,1,MPI_COMM_WORLD,&status);
        }
    }else{
        for(i=0;i<pid%p_sqrt;i++){
            MPI_Recv(*new_sub_B,sub_size,MPI_INT,src_B,1,MPI_COMM_WORLD,&status);
            MPI_Send(*sub_B,sub_size,MPI_INT,dest_B,1,MPI_COMM_WORLD);
            
            for(j=0;j<size/p_sqrt;j++){
                for(k=0;k<size/p_sqrt;k++) sub_B[j][k]=new_sub_B[j][k];
            }
        }
    }

    
    //computing sub_C
    mat_mul(size/p_sqrt,size/p_sqrt,size/p_sqrt,sub_A,sub_B,sub_C);
    
    //printf("%d %d\n",pid,is_diagonal(pid,half_pid,num_proc/2));
    
    if(is_diagonal(pid,half_pid,num_proc/2)==1){
        for(i=1;i<p_sqrt;i++){
            MPI_Send(*sub_A,sub_size,MPI_INT,dest_A,2,MPI_COMM_WORLD);
            MPI_Send(*sub_B,sub_size,MPI_INT,dest_B,3,MPI_COMM_WORLD);
            MPI_Recv(*sub_A,sub_size,MPI_INT,src_A,2,MPI_COMM_WORLD,&status);
            MPI_Recv(*sub_B,sub_size,MPI_INT,src_B,3,MPI_COMM_WORLD,&status);
            mat_mul(size/p_sqrt,size/p_sqrt,size/p_sqrt,sub_A,sub_B,sub_C);
            //printf("1 after sr\n");
        }
    }else{
        for(i=1;i<p_sqrt;i++){
            MPI_Recv(*new_sub_A,sub_size,MPI_INT,src_A,2,MPI_COMM_WORLD,&status);
            MPI_Recv(*new_sub_B,sub_size,MPI_INT,src_B,3,MPI_COMM_WORLD,&status);
            MPI_Send(*sub_A,sub_size,MPI_INT,dest_A,2,MPI_COMM_WORLD);
            MPI_Send(*sub_B,sub_size,MPI_INT,dest_B,3,MPI_COMM_WORLD);
            //sub_A = new_sub_A;
            for(j=0;j<size/p_sqrt;j++){
                for(k=0;k<size/p_sqrt;k++) sub_A[j][k]=new_sub_A[j][k];
            }
            //sub_B = new_sub_B;
            for(j=0;j<size/p_sqrt;j++){
                for(k=0;k<size/p_sqrt;k++) sub_B[j][k]=new_sub_B[j][k];
            }
            mat_mul(size/p_sqrt,size/p_sqrt,size/p_sqrt,sub_A,sub_B,sub_C);
            //printf("0 after rs\n");
        }
    }
    
    
    
    //send sub_C to master
    if(pid!=0){
        MPI_Send(*sub_C,sub_size,MPI_INT,0,4,MPI_COMM_WORLD);
    }
    
    //master gather all sub_C into mat_C
    if(pid==0){
        for(i=0;i<size/p_sqrt;i++){
            for(j=0;j<size/p_sqrt;j++){
                mat_C[i][j]=sub_C[i][j];
            }
        }
        int row_index = 0;
        int col_index = 0;
        for(i=1;i<num_proc;i++){
            MPI_Recv(*sub_C,sub_size,MPI_INT,i,4,MPI_COMM_WORLD,&status);
            row_index = (size/p_sqrt)*(i/p_sqrt);
            col_index = (size/p_sqrt)*(i%p_sqrt);
            for(j=0;j<size/p_sqrt;j++){
                for(k=0;k<size/p_sqrt;k++){
                    mat_C[row_index+j][col_index+k]=sub_C[j][k];
                }
            }
        }
        end=MPI_Wtime();
        printf("Martix Size\tSequential \t Parallel \t Speed Up\n");
        printf("%d(%d cores)\t%.6f\t%.6f\t%.6f\n", size, num_proc, seq, end-begin, seq/(end-begin));
    }
    /*
    if(pid==0){
        
        
        printf("Execution time of size %d matrix multiplication is %.6f\n",size,end-begin);
    }*/

    MPI_Finalize();
}