#include "answer06.h"
#include <stdio.h>
#include <stdlib.h>

void print(int *partition, int length){
	int i;
	printf("= ");
	for(i = 0; i < length; i++){
		if(i != 0) printf(" + ");
		printf("%d", partition[i]);	
	}
	printf("\n");
}

void partitionA(int size, int *partition, int index){
	if(size == 0){
		print(partition, index);
		return;	
	}
	int i;
	for(i = 1; i <= size; i++){
		partition[index] = i;
		partitionA(size - i, partition, index + 1);
	}

}

void partitionincre(int size, int *partition, int index){
	if(size ==0){
		print(partition, index);
		return;
	}
	int i;
	int start;
	if(index == 0)
		start = 1;
	else
		start = partition[index-1] + 1;
	for(i=start; i<=size; i++){
		partition[index] = i;
		partitionincre(size - i, partition, index+1);	
	}
}

void partitiondecre(int size, int *partition, int index){
	if(size == 0){
		print(partition, index);
		return;
	}
	int i;
	for(i = 1; i <= size; i++){
		if(index == 0 || i < partition[index - 1]){
			partition[index] = i;
			partitiondecre(size - i, partition, index + 1);
		}
	}
}

void partitionAll(int value){
	int *partition1 = malloc(sizeof(int)*value);
	partitionA(value, partition1, 0);
	free(partition1);
}

void partitionIncreasing(int value){
	int *partition2 = malloc(sizeof(int)*value);
	partitionincre(value, partition2, 0);
	free(partition2);
}

void partitionDecreasing(int value){
	int *partition3 = malloc(sizeof(int)*value);
	partitiondecre(value, partition3, 0);
	free(partition3);
}

void partitionod(int size, int *partition, int index){
	if(size == 0){
		print(partition,index);
		return;
	}
	int i;
	for(i = 1; i <= size; i++){
		if(i%2 == 1){
			partition[index] = i;
			partitionod(size-i, partition, index+1);
		}
	}
}

void partitionOdd(int value){
	int *partition4 = malloc(sizeof(int)*value);
	partitionod(value, partition4, 0);
	free(partition4);
}

void partitionev(int size, int *partition, int index){
	if(size == 0){
		print(partition, index);
		return;
	}
	int i;
	for(i = 1; i <= size; i++){
		if(i%2 == 0){
			partition[index] = i;
			partitionev(size-i, partition, index+1);
		}
	}
}

void partitionEven(int value){
	int *partition5 = malloc(sizeof(int)*value);
	partitionev(value, partition5, 0);
	free(partition5);
}

void partitionoande(int size, int *partition, int index){
	if(size == 0){
		print(partition, index);
		return;
	}
	int i;
	for(i = 1; i <= size; i++){
		int a = 0;
		if(index == 0) a = 1;
		else a = (partition[index-1]%2 != i%2);
		if(a == 1){
			partition[index] = i;
			partitionoande(size - i, partition, index + 1);
		}
	}
}


void partitionOddAndEven(int value){
	int *partition6 = malloc(sizeof(int)*value);
	partitionoande(value, partition6, 0);
	free(partition6);
}

int isPrime(int num){
	int i;
	if(num < 2) return 0;
	
	for(i = 2; i < num; i++)
		if(num%i == 0) return 0;
	return 1;
}
void partitionP(int size, int *partition, int index){
	if(size == 0){
		print(partition, index);
		return;
	}
	int i;
	for(i = 1; i <= size; i++){
		if(isPrime(i)){
			partition[index] = i;
			partitionP(size - i, partition, index + 1);
		}
	}
}

void partitionPrime(int value){
	int *partition7 = malloc(sizeof(int)*value);
	partitionP(value, partition7, 0);
	free(partition7);
}
