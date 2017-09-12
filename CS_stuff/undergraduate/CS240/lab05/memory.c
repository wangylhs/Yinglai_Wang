#include<stdio.h>
#include<stdlib.h>

struct List{
    struct List *next;
    long value;    
};
struct List *newNode(struct List *node){
    struct List *p;
    p = (struct List*)malloc(sizeof(struct List));
    if(p==NULL)
        exit(0);
    p->next = node;
    if(node==NULL){
        p -> value = 0;
    }else{
        p -> value = node -> value + 1;
    }
    return p;
}
int main(){
    struct List *p;
    p = newNode(NULL);
    while(1){
        p = newNode(p);
        if((p->value)%100000 == 0){
            printf("%ld\n", p->value);
        }
    }    
}
