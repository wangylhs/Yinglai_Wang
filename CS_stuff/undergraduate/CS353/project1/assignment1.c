#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#define MAX 1000000
int arr[MAX];

typedef struct
{
    int min;
    int max;
    //int *arr;
} data;

void findPrime(int min, int max){
    if(max<2){
        printf("No prime numbers smaller than 2.");
    }
    int i;
    int k=2;
    while((k*k)<=max){
        if(min == 0){
            for(i=k+1; i<max; i++){
                if(arr[i]%k==0 && arr[i]!=0) arr[i]=0;
        }
        }else{
            for(i=min; i<max; i++){
                if(arr[i]%k==0 && arr[i]!=0) arr[i]=0;
            }
        }
        int num = k-1;
        while(num<max){
            if(arr[num]>k && arr[num]!=0){
                k = arr[num];
                break;
            }
            num++;
        }
    }
    /*if(min==0){
    for (i=1; i<max; i++) {
        if(arr[i]!=0)
            printf("%d ", arr[i]);
    }
    }else{
        for (i=min; i<max; i++) {
            if(arr[i]!=0)
                printf("%d ", arr[i]);
        }
    }
    */
}

void *find(void *s){
    data* p = (data*)s;
    int i;
    int prime[MAX];
    int ct=0, j=0;
    
    for(i=0;i<sqrt(MAX);i++){
        if(arr[i]!=0){
            prime[j]=arr[i];
            j++;
            ct++;
        }
    }
    for(i=0;i<ct;i++){
        for(j=p->min-1;j<p->max;j++)
            if(arr[j]%prime[i]==0 && arr[j]!=0) arr[j]=0;
    }
    return NULL;
}

void paralle(int p, int min, int max){
    int len = (max-min+1)/p;
    int count;
    pthread_t p_threads[p];
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    data args[800];
    int i;
    for(i=0; i<p; i++){
        args[i].min = min+i*len;
        
        args[i].max = min+(i+1)*len;
    }
    args[p-1].max = max;
    
    for(count=0;count<p;count++){
        pthread_create(&p_threads[count], &attr, (void*)&find, &args[count]);
    }
    for(count=0;count<p;count++){
        pthread_join(p_threads[count], NULL);
    }
}

int main(){
    int i;
    for(i=0; i<MAX; i++) arr[i] = i+1;
    arr[0]=0;
    findPrime(0,sqrt(MAX));
    
    paralle(8,sqrt(MAX)+1,MAX);
    //printf("\n");
    /*for(i=0; i<MAX; i++){
        if(arr[i]!=0)
            printf("%d ", arr[i]);
    }*/
    
    
    
    return 0;
}