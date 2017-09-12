
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <omp.h>
#include <ctype.h>
#include <stddef.h>
#include <math.h>

#define MAX 100000

typedef struct result_tuple
{
	char* key;
    int count;
    int index;
	
}result_tuple;

typedef struct word {
    char key[50];
}word;

typedef struct Q{
    struct word* work;
    int pos;
    int size;
}Q;

struct Q* initQ(int n){
    struct Q *newQ = (struct Q *) malloc(sizeof(Q));
    newQ->work = (word*)malloc(sizeof(word)*n);
    newQ->pos = -1;
    newQ->size = n-1;
}
void putWork(struct Q* workQ, char *key) {
    if (workQ->pos < (workQ->size)) {
        workQ->pos++;
        strcpy(workQ->work[workQ->pos].key, key);
        //printf("%s\n",key);
    } else printf("ERROR: attempt to add Q element %d\n", workQ->pos+1);
}

char* getWork(struct Q* workQ) {
    if (workQ->pos > -1) {
        char* temp = workQ->work[workQ->pos].key;
        //printf("%d %s\n",workQ->pos,workQ->work[workQ->pos].key);
        workQ->pos--;
        return temp;
    } else printf("ERROR: attempt to get work from empty Q %d\n", workQ->pos);
}

void convert_word(char *p){
	char *src = p;
	char *dest = p;
	while(*src){
		if(isalpha((unsigned char)*src)!=0){
			if(isupper((unsigned char)*src)){
				/* convert upper case to lower case */
				//printf("%c\n",*src);
				*dest = tolower((unsigned char)*src);
				dest++;
				src++;
			}else{
				/* lower case directly copy */
				*dest++ = *src++;
			}
		}else{
			/* skip if not a alphabet */
			src++;
		}
	}
	*dest=0;
}

void read_word(const char *file, struct Q* workQ){
	FILE *f = fopen(file,"r");
	char tmp_word[50];
    int index = 0;
    
	while(1){
		/* if using feof to check end of file, the last word will be read twice! */
		if(fscanf(f,"%s",tmp_word)!=1) break;
		convert_word(tmp_word);
        //put word into Q
        putWork(workQ,tmp_word);
		//printf("%s\n", tmp_word);
	}
	fclose(f);
}

static unsigned long sdbm_hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;
    
    while (c = *str++)
        hash = c + ((hash << 5) + hash);
        
    return hash;
}

struct result_tuple* init_result(int n){
	result_tuple* array = malloc(sizeof(result_tuple)*n);
	int i;
	for(i=0;i<n;i++){
		array[i].key = NULL;
		array[i].index = 0;
		array[i].count = 0;
	}
	return array;
}

void map(struct Q* workQ, struct result_tuple* array){
	int i,size,index;
	size = workQ->pos+1;
	char* temp;
	for(i=0;i<size;i++){
		temp = getWork(workQ);
		index = sdbm_hash(temp)%MAX;
		if(array[index].key!=NULL){
			array[index].count++;
		}else{
			array[index].key = temp;
			array[index].count = 1;
		}
	}
}

void reducer(struct result_tuple** result, int num_files){
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=1;j<num_files;j++){
			if(result[0][i].key!=NULL){
				result[0][i].count += result[j][i].count;
			}else{
				if(result[j][i].key!=NULL){
					result[0][i].key = result[j][i].key;
					result[0][i].count += result[j][i].count;
				}
			}
	
		}
	}
}

void writer(struct result_tuple* result, int pid){
	
    char file_name[20];
    char s_pid[3];
    sprintf(s_pid,"%d",pid);
    strcpy(file_name,"p_");
    strcat(file_name,s_pid);
    strcat(file_name,"result.txt");
    FILE *f = fopen(file_name,"w");
	if(f==NULL){
		printf("Error on opening result.txt!\n");
		exit(1);
	}
	int i;
	fprintf(f, "WORD\t\tCOUNT\n");
	for(i=0;i<MAX;i++){
		if(result[i].key!=NULL)
			fprintf(f, "%s\t%d\n", result[i].key, result[i].count);
	}
}


int main(int argc, char * argv[]){
	double reader_time,mapper_time,reducer_time,writer_time;
	int num_proc;
	int pid;
	int i;
	int num_files = argc-1;
	int files_per_proc;
	char** file_array;

	MPI_Status status;
	MPI_Init ( &argc, &argv );
    MPI_Comm_size ( MPI_COMM_WORLD, &num_proc); 
    MPI_Comm_rank ( MPI_COMM_WORLD, &pid );

    if(pid==0){
    	if((argc-1)%num_proc!=0){
    		printf("Number of Files %d is not dividable by number of processors %d\n",argc-1,num_proc);
    		printf("Number of processors have to be a power of 2\n");
            printf("Program terminated.\n");
    		MPI_Finalize();
    		exit(1);
    	}
    }

    //distribut files for each processor
    if(num_files%num_proc!=0){
    	files_per_proc = num_files/num_proc + 1;
    	file_array = malloc(files_per_proc*sizeof(char*));
    	for(i=0;i<files_per_proc-1;i++){
    		file_array[i]=argv[pid*files_per_proc+i+1];
    	}
    	for(i=0;i<num_files%num_proc;i++){
    		if(pid==i){
    			file_array[files_per_proc-1]=argv[(files_per_proc-1)*num_proc+i+1];	
    		}
    		
    	}
	}else{
		files_per_proc = num_files/num_proc;
		file_array = malloc(files_per_proc*sizeof(char*));
    	for(i=0;i<files_per_proc;i++){
    		file_array[i]=argv[pid*files_per_proc+i+1];
    	}
	}
     
	struct Q* workQ[files_per_proc];
    result_tuple* result[files_per_proc];


    if(pid==0){
    	reader_time = -MPI_Wtime();
    }

    for(i=0;i<files_per_proc;i++){
    	//workQ[i]=initQ(1000000);
    	workQ[i] = (struct Q *) malloc(sizeof(Q));
    	workQ[i]->work = (word*)malloc(sizeof(word)*1000000);
    	workQ[i]->pos = -1;
    	workQ[i]->size = 1000000-1;
    	result[i]=init_result(MAX);
    }

    #pragma omp parallel for
    for(i=0;i<files_per_proc;i++){
    	//printf("%d %s\n",pid,file_array[i]);
    	read_word(file_array[i],workQ[i]);
    }
    if(pid==0){
        reader_time += MPI_Wtime();
        mapper_time = -MPI_Wtime();
    }

    #pragma omp parallel for
    for(i=0;i<files_per_proc;i++){
    	map(workQ[i],result[i]);
    }
    if(pid==0){
        mapper_time += MPI_Wtime();
        reducer_time = -MPI_Wtime();
    }
    reducer(result,files_per_proc);
    /*
    //the code below does a logP reduction to reduce the result to one file
    int total_times = (int)log2(num_proc);
    int divider,distance,src,dest;
    char temp[50];
    int count;
    int index;
    for(i=0;i<total_times;i++){
        distance = (int)pow((double)2,i);
        divider = (int)pow((double)2,i+1);
        if(i==0){
            if(pid%2==0){
                src = pid+1;
                while(1){
                    MPI_Recv(temp,50,MPI_CHAR,src,0,MPI_COMM_WORLD,&status);
                    if(temp[0]=='@'){
                        break;
                    }else{
                        index = sdbm_hash(temp)%MAX;
                        MPI_Recv(&count,1,MPI_INT,src,1,MPI_COMM_WORLD,&status);
                        result[0][index].count += count;
                    }
                }
            }else{
                dest = pid-1;
                char buffer[50];
                for(i=0;i<MAX;i++){
                    if(result[0][i].key!=NULL){
                        strcpy(buffer,result[0][i].key);
                        *(buffer+strlen(buffer))='\0';
                        MPI_Send(buffer,strlen(buffer)+1,MPI_CHAR,dest,0,MPI_COMM_WORLD);
                        MPI_Send(&result[0][i].count,1,MPI_INT,dest,1,MPI_COMM_WORLD);
                    }
                }
                char a = '@';
                MPI_Send(&a,1,MPI_CHAR,dest,0,MPI_COMM_WORLD);
            }
        }else{
            if(pid%divider==0){
                src = pid+distance;
                while(1){
                    MPI_Recv(temp,50,MPI_CHAR,src,0,MPI_COMM_WORLD,&status);
                    if(temp[0]=='@'){
                        break;
                    }else{
                        index = sdbm_hash(temp)%MAX;
                        MPI_Recv(&count,1,MPI_INT,src,1,MPI_COMM_WORLD,&status);
                        result[0][index].count += count;
                    }
                }
            }
            if(pid%distance==0 && pid%divider!=0){
                dest = pid - distance;
                char buffer[50];
                for(i=0;i<MAX;i++){
                    if(result[0][i].key!=NULL){
                        strcpy(buffer,result[0][i].key);
                        *(buffer+strlen(buffer))='\0';
                        MPI_Send(buffer,strlen(buffer)+1,MPI_CHAR,dest,0,MPI_COMM_WORLD);
                        MPI_Send(&result[0][i].count,1,MPI_INT,dest,1,MPI_COMM_WORLD);
                    }
                }
                char a = '@';
                MPI_Send(&a,1,MPI_CHAR,dest,0,MPI_COMM_WORLD);
            }
        }

    }
    */
    if(pid==0){
        reducer_time += MPI_Wtime();
        writer_time = -MPI_Wtime();
    }

    writer(result[0],pid);

    if(pid==0){
        writer_time += MPI_Wtime();
        printf("Total Run time for %d files using %d cores is %.6f\n",
            num_files,num_proc,reader_time+mapper_time+reducer_time+writer_time);
        printf("reader_time is %.6f\n",reader_time);
        printf("mapper_time is %.6f\n",mapper_time);
        printf("reducer_time is %.6f\n",reducer_time);
        printf("writer_time is %.6f\n",writer_time);
    }

    MPI_Finalize();
}