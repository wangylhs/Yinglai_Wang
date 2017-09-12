/*
* Project_large step1
* Yinglai Wang, Youngsol Koh 
* wang1105		koh0
*
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#define MAX 100000			//max distinct word

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
    int i;
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
    } else printf("ERROR: attempt to add Q element%d\n", workQ->pos+1);
}

char* getWork(struct Q* workQ) {
    if (workQ->pos > -1) {
        char* temp = workQ->work[workQ->pos].key;
        //printf("%d %s\n",workQ->pos,workQ->work[workQ->pos].key);
        workQ->pos--;
        return temp;
    } else printf("ERROR: attempt to get work from empty Q%d\n", workQ->pos);
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

void writer(struct result_tuple* result){
	FILE *f = fopen("result.txt","w");
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

int main(int argc, char const *argv[]){
	double time;
	int i;
	int num_files;
	if(argc<=1){
		printf("usage: ./map_omp [input files]... \n");
		return 0;
	}else{
		num_files = argc-1;
	}

	struct Q* workQ[num_files];
	result_tuple* result[num_files];
	for(i=0;i<num_files;i++){
		workQ[i] = initQ(1000000);
		result[i] = init_result(MAX);
	}

	time = -omp_get_wtime();

	#pragma omp parallel for
	for(i=0;i<num_files;i++){
		read_word(argv[i+1],workQ[i]);
	}

	#pragma omp parallel for
	for(i=0;i<num_files;i++){
		map(workQ[i],result[i]);
	}

	reducer(result,num_files);
	time += omp_get_wtime();
	printf("Run time: %f\n", time);
	writer(result[0]);

}
























